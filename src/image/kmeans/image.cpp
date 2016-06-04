#include "image.h"

bool Image::open(string name)
{
	attr.name = name;
	mat = imread(attr.name.data());
	if (mat.empty())
	{
		cout << "the image: " << attr.name << " is not exist" << endl;
		return false;
	}
	return true;
}


void Image::setAttribute(int gender, int year, int type)
{
	attr.gender = gender;
	attr.year = year;
	attr.type = type;
}

void Image::setAttribute(int gender, int year, int type, int num)
{
	attr.gender = gender;
	attr.year = year;
	attr.type = type;
	attr.num = num;
}

void Image::show()
{
	Mat newMat(50, 250, CV_8UC3, cv::Scalar(0,0,0));
	for (int i = 0; i < newMat.rows; i++)
	{
		for (int j = 0; j < newMat.cols; j++)
		{
			newMat.at<uchar>(i, j*3+0) = color[j/50].b;
			newMat.at<uchar>(i, j*3+1) = color[j/50].g;
			newMat.at<uchar>(i, j*3+2) = color[j/50].r;
		}
	}
	imshow("src", mat);
	imshow("lalala", newMat);
	waitKey(0);

}

void Image::setColor()
{
	cluster.run(mat, color);
	// show();
}

void Image::getColor(Node node[C_NUM])
{
	for (int i = 0; i < C_NUM; i++)
	{
		node[i] = color[i];
	}
}