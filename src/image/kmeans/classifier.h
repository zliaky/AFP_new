#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include "image.h"
#define R(h) h >= 337.5 || h < 22.5
#define YR(h) h >= 22.5 && h < 52.5
#define Y(h) h >= 52.5 && h < 75
#define GY(h) h >= 75 && h < 107.5
#define G(h) h >= 107.5 && h < 137.5
#define BG(h) h >= 137.5 && h < 172.5
#define B(h) h >= 172.5 && h < 212.5
#define PB(h) h >= 212.5 && h < 255
#define P(h) h >= 255 && h < 300
#define RP(h) h >= 300 && h < 337.5

class Classifier
{
	Image img;
	Node seed[C_NUM];
	int emotion[4][7];
	ofstream fout;
	void pixelProcess();
	void analysis();
public:
	void run();
};

/*
 *emotion:
 *0刺激：
 *  0非常刺激，1刺激，2稍微刺激，3稍微平静，4平静，5非常平静，6没有刺激
 *1热情：
 *  0非常热情，1热情，2冷淡
 *2温度：
 *  0非常暖和，1暖和，2稍微暖和，3中性的温度感，4稍微凉爽，5凉爽，6非常凉爽
 *3性格：
 *  0活泼，1忧郁
 */


#endif