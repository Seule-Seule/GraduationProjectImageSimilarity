#ifndef COLORHISTOGRAMEQUALIZATION_HPP
#define COLORHISTOGRAMEQUALIZATION_HPP
#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

#include <QDebug>

#include <io.h>
#include <direct.h>
#include <fstream>

void ColorHistEqualizationTest1();
void ColorHistEqualizationTest2();
void ColorHistEqualizationTest3();
void ColorHistEqualizationTest4();
double ColorHistEqualization(Mat &leftImage, Mat &rightImage, string leftSavePath, string rightSavePath);

#endif // COLORHISTOGRAMEQUALIZATION_HPP
