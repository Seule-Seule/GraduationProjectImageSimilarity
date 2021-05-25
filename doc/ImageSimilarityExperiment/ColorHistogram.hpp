#ifndef COLORHISTOGRAM_HPP
#define COLORHISTOGRAM_HPP

#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

#include <QDebug>

#include <io.h>
#include <direct.h>
#include <fstream>

void ColorHistTest1();
void ColorHistTest2();
void ColorHistTest3();
void ColorHistTest4();

double ColorHistogram(Mat &leftImage, Mat &rightImage, string leftSavePath, string rightSavePath);

#endif // COLORHISTOGRAM_HPP
