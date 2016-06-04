#ifndef __NODE_H__
#define __NODE_H__

#include "defines.h"

class Node
{
public:
	Node() {}
	int r, g, b;
	int rank;
	int h, s, v;
};

#endif