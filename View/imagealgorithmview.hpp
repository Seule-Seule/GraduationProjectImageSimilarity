#ifndef IMAGEALGORITHMVIEW_HPP
#define IMAGEALGORITHMVIEW_HPP

#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

#include <QObject>
#include <QString>

using namespace cv;

class ImageAlgorithmView : public QObject
{
    Q_OBJECT
public:
    explicit ImageAlgorithmView(QObject *parent = nullptr);

    enum  WorkSpace{
        RGB,
        HSV,
        GRAY
    };

    enum HashType
    {
        eAHASH,
        ePHASH,
        eDHASH
    };

signals:
    void debugMessageSig(QString);
    void detectMessageSig(QString);

private :
    void update();
    void debugMessage(QString message);
    void detectMessage(QString message);
    void DrawHist(String window_name, int width, int height, QVector<Mat> &hist_in);
    void splitMat(const Mat &srcImg,int m,int n, QVector<Mat> &ceilImg);

    int HanmingDistance(QString &str1, QString &str2);
    QString aHashValue(const Mat& src);
    QString pHashValue(const Mat& src);
    QString dHashValue(const Mat& src);
public:

    // 直方图
    void CompImageHist(const Mat &src_in,WorkSpace ws, int id);
    void ColorHistogram(const Mat &leftImage,const Mat &rightImage);
    double NormalizedColorHistogram(const Mat &leftImage,const Mat &rightImage, bool sengMessage = true);
    void SubNormalizedColorHistogram(const Mat &leftImage,const Mat &rightImage, int scale = 3);

    // 哈希算法
    double HASH(HashType type, const Mat &leftImage, const Mat &rightImage);

    // sift
    double SIFT(const Mat &leftImage, const Mat &rightImage);

};

#endif // IMAGEALGORITHMVIEW_HPP
