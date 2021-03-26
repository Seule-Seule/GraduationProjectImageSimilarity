#ifndef IMAGEALGORITHM_HPP
#define IMAGEALGORITHM_HPP

#include "Tools/tool.hpp"

#include "opencv2/opencv.hpp"
#include<opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

#include <QObject>

using namespace cv;

class ImageAlgorithm : public QObject
{
    Q_OBJECT

public:
    ImageAlgorithm(QObject *parent);

public:
    enum imageColorSpace{
        GRAY,
        RGB,
        YUV
    };

public:
    void histogramImagesSimilarity(const Mat &leftImage,const Mat &rightImage);
    void aptiveHistogramEqualization(Mat &leftImage, Mat &rightImage);
    void scaleInvariantFeatureTransform(Mat &leftImage, Mat &rightImage);

    void histogramEequalization(const Mat &src, imageColorSpace colorSpace = GRAY);
    void histogramBuild(const Mat &src);

signals:
    void sendStatusBarMessageSig(QString message, int timeout);
    void sendDebugMessageSig(QString message);
    void sendDetectMessageSig(QString);

private:
    void debugShowMessage(QString message);
    void DetectShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout);

};

#endif // IMAGEALGORITHM_HPP
