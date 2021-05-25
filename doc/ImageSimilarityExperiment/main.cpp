#include "imageprocess.hpp"
#include "ColorHistogram.hpp"
#include "colorhistogramequalization.hpp"
#include "colorhistsubequalization.hpp"
#include "hash.hpp"
#include "sift.hpp"

int main(int argc, char *argv[])
{

//    ImageProcess();
    //ColorHistTest1();
//    ColorHistTest2();
//    ColorHistTest3();
//    ColorHistTest4();

//    ColorHistEqualizationTest1();
//    ColorHistEqualizationTest2();
//    ColorHistEqualizationTest3();
//    ColorHistEqualizationTest4();

//    ColorHistSubEqualizationTest1();

    //siftTest();

//test();

// 毕设 测试数据
// 关于颜色直方图

    string imagePath = "Z:/testImages/sImage/";

//    //不相似（实际上是不相同）图像，但具有相同的直方图
//    cv::Mat image1 = cv::imread(imagePath+string("S0101.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0104.BMP"), -1);
//    string savePath = string("./");
//    double ret = ColorHistogram(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

    //相似（实际上是相同）图像，但具有不同的直方图灰度范围不同
//    cv::Mat image1 = cv::imread(imagePath+string("S0201.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0202.BMP"), -1);
//    string savePath = string("./");
//    double ret = ColorHistogram(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

    // 相似（实际上是相同）图像，但具有不同的分辨率
//    cv::Mat image1 = cv::imread(imagePath+string("S0201.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"), -1);
//    string savePath = string("./");
//    double ret = ColorHistogram(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

    // 相似（实际上是相同）的图像，但具有不同的直方图
//    cv::Mat image1 = cv::imread(imagePath+string("D0401.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("D0401-3.BMP"),-1);
//    string savePath = string("./");
//    double ret = ColorHistogram(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

//    //相似（实际上是相同）的图像，但具有不同的分辨率
//    cv::Mat image1 = cv::imread(imagePath+string("D0401-1.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("D0401-5.BMP"),-1);
//    string savePath = string("./");
//    double ret = ColorHistogram(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;


//    // 同一幅图像验证正确
//    cv::Mat image1 = cv::imread(imagePath+string("D0401-5.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("D0401-5.BMP"),-1);
//    string savePath = string("./");
//    double ret = ColorHistogram(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

//    // 验证c错误
//    cv::Mat image1 = cv::imread(imagePath+string("D0401-1.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0201.BMP"),-1);
//    string savePath = string("./");
//    double ret = ColorHistogram(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

    // 正确
//    cv::Mat image1 = cv::imread(imagePath+string("S0203.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"),-1);
//    string savePath = string("./");
//    double ret = ColorHistEqualization(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

//    // 验证c错误
//    cv::Mat image1 = cv::imread(imagePath+string("S0104.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"),-1);
//    string savePath = string("./");
//    double ret = ColorHistEqualization(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

    // 分辨率
//    cv::Mat image1 = cv::imread(imagePath+string("S0201.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"),-1);
//    string savePath = string("./");
//    double ret = ColorHistEqualization(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
//    qDebug() << ret;

    // 正确性
//    cv::Mat image1 = cv::imread(imagePath+string("S0203.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"),-1);
//    string savePath = string("./");
//    double ret = colorHistSubEqualization(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"),3);
//    qDebug() << ret;

//    // 错误
//    cv::Mat image1 = cv::imread(imagePath+string("D0401.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"),-1);
//    string savePath = string("./");
//    double ret = colorHistSubEqualization(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"),3);
//    qDebug() << ret;

    //////////////////////////////////////////////////////////////////
    // 哈希算法

    // 正确性
//    cv::Mat image1 = cv::imread(imagePath+string("D0401.BMP"), -1);
//    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"),-1);
//    hashTest(image1, image2);

    ////////////////////////////////////////////////////////////////////
    //SIFT

    // 正确
    cv::Mat image1 = cv::imread(imagePath+string("D0401.BMP"), -1);
    cv::Mat image2 = cv::imread(imagePath+string("S0203.BMP"),-1);
    string savePath = string("./");
    double ret = sift(image1, image2,savePath+string("1.jpg"), savePath+string("2.jpg"));
    qDebug() << ret;


    return 0;
}
