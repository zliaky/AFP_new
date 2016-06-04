#include "cluster.h"

void Cluster::read()
{
	imgNodeNum = 0;
	for (int x = 0; x < height; x += M_HEIGHT)
	{
		for (int y = 0; y < width; y += M_WIDTH)
		{
			imgNode[imgNodeNum].r = mat.at<uchar>(x, y*mat.channels()+2);
			imgNode[imgNodeNum].g = mat.at<uchar>(x, y*mat.channels()+1);
			imgNode[imgNodeNum].b = mat.at<uchar>(x, y*mat.channels()+0);
			imgNodeNum++;
		}
	}
}

double Cluster::pow(int n, int r)
{
	double ans = 1;
	for (int i = 0; i < r; i++)
	{
		ans *= n;
	}
	return ans;
}

double Cluster::distance(Node a, Node b)
{
	double sum = 0;
	sum += pow((a.r - b.r), 2);
	sum += pow((a.g - b.g), 2);
	sum += pow((a.b - b.b), 2);
	sum = sqrt(sum);
	return sum;
}

void Cluster::init()
{
	width = mat.cols;
	height = mat.rows;
	for (int i = 0; i < MAXN; i++)
	{
		imgNode[i].rank = -1;
	}
	read();
	for (int i = 0; i < C_NUM; i++)
	{
		seed[i] = imgNode[imgNodeNum/C_NUM*i];
		seed[i].rank = i;
	}
}

void Cluster::updateSeed()
{
	int r[C_NUM], g[C_NUM], b[C_NUM], num[C_NUM];
	Node newNode[C_NUM];
	for (int i = 0; i < C_NUM; i++)
	{
		r[i] = g[i] = b[i] = num[i] = 0;
	}
	for (int i = 0; i < C_NUM; i++)
	{
		for (int j = 0; j < imgNodeNum; j++)
		{
			if (imgNode[j].rank != i) continue;
			r[i] += imgNode[j].r;
			g[i] += imgNode[j].g;
			b[i] += imgNode[j].b;
			num[i]++;
		}
	}
	for (int i = 0; i < C_NUM; i++)
	{
		if (num[i] > 0)
		{
			r[i] /= num[i];
			g[i] /= num[i];
			b[i] /= num[i];
		}
	}
	for (int i = 0; i < C_NUM; i++)
	{
		newNode[i].r = r[i];
		newNode[i].g = g[i];
		newNode[i].b = b[i];
	}
	for (int i = 0; i < C_NUM; i++)
	{
		double minD = distance(imgNode[0], newNode[i]);
		for (int j = 0; j < imgNodeNum; j++)
		{
			if (imgNode[j].rank != i) continue;
			double dis = distance(imgNode[j], newNode[i]);
			if (dis < minD)
			{
				minD = dis;
				seed[i] = imgNode[j];
			}
		}
	}
}

void Cluster::updateCluster()
{
	for (int i = 0; i < imgNodeNum; i++)
	{
		double minD = distance(seed[0], imgNode[i]);
		int flag = 0;
		for (int j = 1; j < C_NUM; j++)
		{
			double dis = distance(seed[j], imgNode[i]);
			if (dis < minD)
			{
				minD = dis;
				flag = j;
			}
		}
		imgNode[i].rank = flag;
	}
}

void Cluster::run(Mat mat, Node node[C_NUM])
{
	this->mat = mat;
	init();
	updateCluster();
	for (int i = 0; i < ITER_TIME; i++)
	{
		updateSeed();
		updateCluster();
	}
	for (int i = 0; i < C_NUM; i++)
	{
		node[i] = seed[i];
	}
}