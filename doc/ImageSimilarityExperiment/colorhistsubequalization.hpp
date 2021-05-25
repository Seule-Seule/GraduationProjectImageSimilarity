#ifndef COLORHISTSUBEQUALIZATION_HPP
#define COLORHISTSUBEQUALIZATION_HPP

#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

#include <QDebug>

#include <io.h>
#include <direct.h>
#include <fstream>

void ColorHistSubEqualizationTest1();

double colorHistSubEqualization(Mat &leftImage, Mat &rightImage, string leftSavePath, string rightSavePath, size_t scale = 3/*3x3*/);

#endif // COLORHISTSU；
