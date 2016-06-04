#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include "node.h"

#define M_WIDTH 20
#define M_HEIGHT 20
#define ITER_TIME 10

class Cluster
{
	Node imgNode[MAXN];
	int imgNodeNum;
	Mat mat;
	int width, height;
	Node seed[C_NUM];
public:
	void read();
	double pow(int n, int r);
	double distance(Node a, Node b);
	void init();
	void updateSeed();
	void updateCluster();
	void run(Mat mat, Node node[C_NUM]);
};

#endif