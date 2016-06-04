#include "classifier.h"

void Classifier::pixelProcess()
{
	DIR *dp;
	struct dirent *dirp;
	int n = 0;
	if ((dp=opendir("../../../images")) == NULL)
		printf("Can't open dir\n");
	fout.open("../../txt/vector_emotion.txt");
	while ((dirp=readdir(dp)) != NULL)
	{
		if (strcmp(dirp->d_name, ".") == 0) continue;
		if (strcmp(dirp->d_name, "..") == 0) continue;
		char prefix[200] = "../../../images/";
		if (!img.open(strcat(prefix,dirp->d_name))) continue;
		cout << n << ": succeed opening file " << prefix << endl;
		img.setColor();
		img.getColor(seed);
		analysis();
		n++;
	}
	fout.close();
	closedir(dp);
}

void Classifier::analysis()
{
	Mat img(1, C_NUM, CV_8UC3, cv::Scalar(0,0,0));
	for (int i = 0; i < C_NUM; i++)
	{
		img.at<uchar>(0, i*3+0) = seed[i].b;
		img.at<uchar>(0, i*3+1) = seed[i].g;
		img.at<uchar>(0, i*3+2) = seed[i].r;
	}
	cvtColor(img, img, CV_BGR2HSV);
	for (int i = 0; i < C_NUM; i++)
	{
		seed[i].h = 1.0*img.at<uchar>(0, i*3+0)/255*359;
		seed[i].s = 1.0*img.at<uchar>(0, i*3+1)/255*100;
		seed[i].v = 1.0*img.at<uchar>(0, i*3+2)/255*100;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			emotion[i][j] = 0;
		}
	}
	for (int i = 0; i < C_NUM; i++)
	{
		if (seed[i].v < 50)
		{
			emotion[0][6]++;
			emotion[2][3]++;
		}
		if (seed[i].s < 35)
		{
			emotion[3][1]++;
		}
		if (seed[i].s > 65)
		{
			emotion[3][0]++;
		}
		if (seed[i].v > 50 && seed[i].s > 35)
		{
			int h = seed[i].h;
			if (R(h))
			{
				emotion[0][0]++;
				emotion[1][0]++;
				emotion[2][0]++;
			}
			if (YR(h))
			{
				emotion[0][1]++;
				emotion[1][1]++;
				emotion[2][1]++;
			}
			if (Y(h))
			{
				emotion[0][2]++;
				emotion[2][2]++;
			}
			if (GY(h))
			{
				emotion[0][3]++;
				emotion[2][3]++;
			}
			if (G(h))
			{
				emotion[0][4]++;
				emotion[2][4]++;
			}
			if (BG(h))
			{
				emotion[0][5]++;
				emotion[2][6]++;
			}
			if (B(h))
			{
				emotion[0][6]++;
				emotion[2][5]++;
			}
			if (PB(h))
			{
				emotion[0][6]++;
				emotion[1][2]++;
			}
			if (P(h))
			{
				emotion[0][2]++;
				emotion[2][3]++;
			}
			if (RP(h))
			{
				emotion[0][1]++;
				emotion[2][2]++;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i == 1 && j >= 3) break;
			if (i == 3 && j >= 2) break;
			fout << emotion[i][j] << " ";
		}
	}
	fout << endl;
}

void Classifier::run()
{
	pixelProcess();
}


