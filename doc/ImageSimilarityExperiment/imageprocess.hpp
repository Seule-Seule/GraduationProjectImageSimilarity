#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

#include <QDebug>

#include <io.h>
#include <direct.h>
#include <fstream>

void ImageProcess();
void getFiles(string path, vector <string> & files);
vector<string> splitString(const std::string &str, const std::string &pattern);
void getInfo(std::string file, map<int, std::string> &info);
void DrawHist(String window_name, int width, int height, QVector<Mat> &hist_in, string SavePath);
void CompImageHist(const Mat &src, string SavePath);

#endif // IMAGEPROCESS_HPP
