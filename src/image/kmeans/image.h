#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "attribute.h"
#include "cluster.h"

class Image
{
private:
	Attribute attr;
	Mat mat;
	Node color[C_NUM];
	Cluster cluster;
public:
	bool open(string name);
	void setAttribute(int gender, int year, int type);
	void setAttribute(int gender, int year, int type, int num);
	void setColor();
	void getColor(Node node[C_NUM]);
	void show();
};


#endif