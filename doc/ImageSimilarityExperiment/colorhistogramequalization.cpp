#include "colorhistogramequalization.hpp"
#include "imageprocess.hpp"

#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

#include <QDebug>

#include <io.h>
#include <direct.h>
#include <fstream>

double ColorHistEqualization(Mat &leftImage, Mat &rightImage, string leftSavePath, string rightSavePath)
{
    if (leftImage.empty() || rightImage.empty()){
        qDebug() << ("histogramImagesSimilarity image not load !");
        return -1;
    }
    //qDebug() << ("histogramImagesSimilarity begin !");

    Mat leftSrc, rightSrc;
    if(leftImage.channels() == 1 && rightImage.channels() == 1){
        leftSrc = leftImage;
        rightSrc = rightImage;
    }
    else if(leftImage.channels() == 3 && rightImage.channels() == 3){
        cvtColor(leftImage, leftSrc, CV_RGB2HSV);
        cvtColor(rightImage, rightSrc, CV_RGB2HSV);
    }

    // 计算直方图
    Mat histLeft, histRight;
    if(leftImage.channels() == 1 && rightImage.channels() == 1){
        float hranges[] = {0, 256};
        const float *ranges[] = {hranges};   // 这里需要为const类型
        int size = 256;
        int channels = 0;
        calcHist(&leftSrc, 1, &channels, Mat(), histLeft, 1, &size, ranges, true, false);
        calcHist(&rightSrc, 1, &channels, Mat(), histRight, 1, &size, ranges, true, false);
    }
    else if(leftImage.channels() == 3 && rightImage.channels() == 3){
        int h_bins = 50, s_bins = 60;
        int histsize[] = { h_bins,s_bins };
        float h_ranges[] = { 0,180 };
        float s_ranges[] = { 0,256 };
        const float *ranges[] = { h_ranges,s_ranges };
        int channels3[] = { 0,1 };
        calcHist(&leftSrc, 1, channels3, Mat(), histLeft, 1, histsize, ranges, true, false);
        calcHist(&rightSrc, 1, channels3, Mat(), histRight, 1, histsize, ranges, true, false);
    }

    // 全局归一化
    normalize(histLeft, histLeft, 0, leftSrc.rows, NORM_MINMAX, -1, Mat());
    normalize(histRight, histRight, 0, rightSrc.rows, NORM_MINMAX, -1, Mat());

    // 保存直方图
    std::vector<std::string> retL = splitString(leftSavePath, ".");
    std::vector<std::string> retR = splitString(rightSavePath, ".");
    if(retL.size() > 2)
    {
        string histLeftSavePath =  retL[0]+ string("_hist.jpg");
        string histRightSavePath = retR[0] + string("_hist.jpg");
        CompImageHist(leftSrc, histLeftSavePath, true);
        CompImageHist(rightSrc, histRightSavePath, true);
    }
    else
    {
        string histLeftSavePath =  string(".") + retL[0]+ string("_hist.jpg");
        string histRightSavePath = string(".") + retR[0] + string("_hist.jpg");
        CompImageHist(leftSrc, histLeftSavePath, true);
        CompImageHist(rightSrc, histRightSavePath, true);
    }

    // 计算相似性
    double result =  0.0 ;
    result = compareHist(histLeft, histRight, CV_COMP_CORREL);
    QString messageCorrel = QString(QString("ColorHistEqualization Images Similarity::") + QString::number(result));
    qDebug() << (messageCorrel);
    //qDebug() << ("histogramImagesSimilarity end !");

    //    // 写入结果  暂时不写 整理数据时图片缩放写入的字体会变形
    //    putText(leftSrc, std::to_string(result), Point(100, 100), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255),2, LINE_AA);
    //    putText(rightSrc, std::to_string(result), Point(100, 100), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255),2, LINE_AA);

    if (_access(leftSavePath.c_str(), 0) == -1)
        imwrite(leftSavePath, leftSrc);
    if (_access(rightSavePath.c_str(), 0) == -1)
        imwrite(rightSavePath, rightSrc);

    return result;
}

//同一幅图像，不同分辨率情况下相似度检验
void ColorHistEqualizationTest1()
{
    std::string path("Z:/testImages/images");

    std::string resultPath = path + string("/ColorHistEqualizationTest1");
    if (_access(resultPath.c_str(), 0) == -1)
        _mkdir(resultPath.c_str());

    // 存储结果： 名字1 分辨率1 分辨率2 检测结果
    std::string resultCsvPath = path + string("/ColorHistEqualizationTest1/result.csv");
    ofstream csvFile;
    //ios::app指从文件尾开始输出
    csvFile.open(resultCsvPath,ios::out|ios::app);
    if(!csvFile)
    {
        qDebug() << ("创建CSV文件失败！");
        return ;
    }
    csvFile << "图片名" << "," << "分辨率1" << "," << "分辨率2" << "," << "相似性检验结果" << "\n";

    vector<std::string> files;
    getFiles(path, files);

    map<int, std::string> info;
    string calendar;
    string fileName;
    vector<string> resolutions;
    for (string file : files)
    {
        getInfo(file, info);
        calendar = info[0];
        fileName = info[2];
        resolutions = splitString(info[4], ",");

        // 中间分辨率图片 作为基准图片
        string imageName0 = calendar+string("_")+fileName+string("_")+ resolutions[resolutions.size()/2 ]+string(".jpg");
        string imagePath0 = path + string("/") + resolutions[resolutions.size()/2 ] + string("/") + imageName0;

        string resultImagePath = path + string("/ColorHistEqualizationTest1/") + fileName;
        if (_access(resultImagePath.c_str(), 0) == -1)
            _mkdir(resultImagePath.c_str());

        string imageSavePath0 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[resolutions.size()/2 ]+string("_base.jpg");
        for (size_t index = 1; index < resolutions.size(); index++){
            // 待检验图片
            string imageName1 = calendar+string("_")+fileName+string("_")+ resolutions[index]+string(".jpg");
            string imagePath1 = path + string("/") + resolutions[index] + string("/") + imageName1;
            string imageSavePath1 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[index]+string("_test.jpg");

            Mat image0 = imread(imagePath0);
            Mat image1 = imread(imagePath1);
            double result = ColorHistEqualization(image0, image1, imageSavePath0, imageSavePath1);
            csvFile << fileName << "," << resolutions[resolutions.size()/2] << "," << resolutions[index] << "," << result << endl;
        }
    }
    csvFile.close();
}

//图像不同但相似的同分辨率
void ColorHistEqualizationTest2()
{
    std::string path("Z:/testImages/images");

    std::string resultPath = path + string("/ColorHistEqualizationTest2");
    if (_access(resultPath.c_str(), 0) == -1)
        _mkdir(resultPath.c_str());

    // 存储结果： 名字1 分辨率1 分辨率2 检测结果
    std::string resultCsvPath = path + string("/ColorHistEqualizationTest2/result.csv");
    ofstream csvFile;
    //ios::app指从文件尾开始输出
    csvFile.open(resultCsvPath,ios::out|ios::app);
    if(!csvFile)
    {
        qDebug() << ("创建CSV文件失败！");
        return ;
    }
    csvFile << "图片1名" << "," << "图片2名" << "," << "分辨率" << "," << "相似性检验结果" << "\n";

    vector<std::string> files;
    getFiles(path, files);

    map<int, std::string> info;
    string calendar;
    string fileName;
    vector<string> resolutions;
    for (string file : files)
    {
        getInfo(file, info);
        calendar = info[0];
        fileName = info[2];
        resolutions = splitString(info[4], ",");

        string resultImagePath = path + string("/ColorHistEqualizationTest2/") + fileName;
        if (_access(resultImagePath.c_str(), 0) == -1)
            _mkdir(resultImagePath.c_str());

        for (size_t index = 1; index < resolutions.size(); index++){
            // 原图
            string imageName0 = calendar+string("_")+fileName+string("_")+ resolutions[index]+string(".jpg");
            string imagePath0 = path + string("/") + resolutions[index] + string("/") + imageName0;
            string imageSavePath0 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[index]+string("_base.jpg");

            // 相似图
            string imageName1 = calendar+string("_")+fileName+string("_")+ resolutions[index]+string("_Similarity.jpg");
            string imagePath1 = path + string("/") + resolutions[index] + string("/") + imageName1;
            string imageSavePath1 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[index]+string("_test.jpg");

            Mat image0 = imread(imagePath0);
            Mat image1 = imread(imagePath1);
            double result = ColorHistEqualization(image0, image1, imageSavePath0, imageSavePath1);
            csvFile << imageName0 << "," << imageName1 << "," << resolutions[index] << "," << result << endl;
        }
    }
    csvFile.close();
}

//图像不同但相似的不同分辨率
void ColorHistEqualizationTest3()
{
    std::string path("Z:/testImages/images");

    std::string resultPath = path + string("/ColorHistEqualizationTest3");
    if (_access(resultPath.c_str(), 0) == -1)
        _mkdir(resultPath.c_str());

    // 存储结果： 名字1 名字2 分辨率1 分辨率2 检测结果
    std::string resultCsvPath = path + string("/ColorHistEqualizationTest3/result.csv");
    ofstream csvFile;
    //ios::app指从文件尾开始输出
    csvFile.open(resultCsvPath,ios::out|ios::app);
    if(!csvFile)
    {
        qDebug() << ("创建CSV文件失败！");
        return ;
    }
    csvFile << "图片名" << ","  <<  "图片名" << "," << "分辨率1" << "," << "分辨率2" << "," << "相似性检验结果" << "\n";

    vector<std::string> files;
    getFiles(path, files);

    map<int, std::string> info;
    string calendar;
    string fileName;
    vector<string> resolutions;
    for (string file : files)
    {
        getInfo(file, info);
        calendar = info[0];
        fileName = info[2];
        resolutions = splitString(info[4], ",");

        // 中间分辨率图片 作为基准图片
        string imageName0 = calendar+string("_")+fileName+string("_")+ resolutions[resolutions.size()/2 ]+string(".jpg");
        string imagePath0 = path + string("/") + resolutions[resolutions.size()/2 ] + string("/") + imageName0;

        string resultImagePath = path + string("/ColorHistEqualizationTest3/") + fileName;
        if (_access(resultImagePath.c_str(), 0) == -1)
            _mkdir(resultImagePath.c_str());

        string imageSavePath0 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[resolutions.size()/2 ]+string("_base.jpg");
        for (size_t index = 1; index < resolutions.size(); index++){
            // 待检验图片
            string imageName1 = calendar+string("_")+fileName+string("_")+ resolutions[index]+string("_Similarity.jpg");
            string imagePath1 = path + string("/") + resolutions[index] + string("/") + imageName1;
            string imageSavePath1 = resultPath+string("/")+ fileName+string("/")+fileName+string("_")+resolutions[index]+string("_test.jpg");

            Mat image0 = imread(imagePath0);
            Mat image1 = imread(imagePath1);
            double result = ColorHistEqualization(image0, image1, imageSavePath0, imageSavePath1);
            csvFile << imageName0 << ","  << imageName1 << "," << resolutions[resolutions.size()/2] << "," << resolutions[index] << "," << result << endl;
        }
    }
    csvFile.close();
}

//  图像不同且不相似的同分辨率和不同分辨率
void ColorHistEqualizationTest4()
{
    std::string path("Z:/testImages/images");
    std::string resultPath = path + string("/ColorHistEqualizationTest4");
    if (_access(resultPath.c_str(), 0) == -1)
        _mkdir(resultPath.c_str());

    // 存储结果： 名字1 名字2 分辨率1 分辨率2 检测结果
    std::string resultCsvPath = path + string("/ColorHistEqualizationTest4/result.csv");
    ofstream csvFile;
    //ios::app指从文件尾开始输出
    csvFile.open(resultCsvPath,ios::out|ios::app);
    if(!csvFile)
    {
        qDebug() << ("创建CSV文件失败！");
        return ;
    }
    csvFile << "图片1名" << ","  <<  "图片2名" << "," << "分辨率1" << "," << "分辨率2" << "," << "相似性检验结果" << "\n";

    vector<std::string> files;
    getFiles(path, files);

    map<int, std::string> info0;
    map<int, std::string> info1;
    string calendar0,calendar1;
    string fileName0, fileName1;
    vector<string> resolutions0, resolutions1;
    for (size_t fileIndex = 0; fileIndex < files.size()-1; fileIndex+=2)
    {
        getInfo(files[fileIndex], info0);
        calendar0 = info0[0];
        fileName0 = info0[2];
        resolutions0 = splitString(info0[4], ",");

        getInfo(files[fileIndex+1], info1);
        calendar1 = info1[0];
        fileName1 = info1[2];
        resolutions1 = splitString(info1[4], ",");

        //  图片1
        string imageName0 = calendar0+string("_")+fileName0+string("_")+ resolutions0[resolutions0.size()/2 ]+string(".jpg");
        string imagePath0 = path + string("/") + resolutions0[resolutions0.size()/2 ] + string("/") + imageName0;

        string resultImagePath = path + string("/ColorHistEqualizationTest4/") + fileName0;
        if (_access(resultImagePath.c_str(), 0) == -1)
            _mkdir(resultImagePath.c_str());
        string imageSavePath0 = resultPath+string("/")+ fileName0+string("/")+fileName0+string("_")+resolutions0[resolutions0.size()/2 ]+string("_base.jpg");

        for (size_t index = 1; index < resolutions1.size(); index++){

            // 图片2
            string imageName1 = calendar1+string("_")+fileName1+string("_")+ resolutions1[index]+string(".jpg");
            string imagePath1 = path + string("/") + resolutions1[index] + string("/") + imageName1;

            string resultImagePath = path + string("/ColorHistEqualizationTest4/") + fileName1;
            if (_access(resultImagePath.c_str(), 0) == -1)
                _mkdir(resultImagePath.c_str());
            string imageSavePath1 = resultPath+string("/")+ fileName1+string("/")+fileName1+string("_")+resolutions1[index]+string("_test.jpg");

            Mat image0 = imread(imagePath0);
            Mat image1 = imread(imagePath1);
            double result = ColorHistEqualization(image0, image1, imageSavePath0, imageSavePath1);
            csvFile << imageName0 << ","  << imageName1 << "," << resolutions0[resolutions0.size()/2] << "," << resolutions1[index] << "," << result << endl;
        }
    }
    csvFile.close();
}
