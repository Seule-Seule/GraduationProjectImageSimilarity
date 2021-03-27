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

signals:
    void debugMessageSig(QString);
    void detectMessageSig(QString);

private :
    void update();
    void debugMessage(QString message);
    void detectMessage(QString message);

public:
    void histogramImagesSimilarity(const Mat &leftImage,const Mat &rightImage);

};

#endif // IMAGEALGORITHMVIEW_HPP
