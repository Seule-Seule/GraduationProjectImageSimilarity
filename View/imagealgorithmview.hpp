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

signals:
    void debugMessageSig(QString);
    void detectMessageSig(QString);

private :
    void update();
    void debugMessage(QString message);
    void detectMessage(QString message);
    void DrawHist(String window_name, int width, int height, QVector<Mat> &hist_in);

public:
    void CompImageHist(const Mat &src_in,WorkSpace ws, int id);
    void HistogramEqualization(const Mat &leftImage,const Mat &rightImage);
    void AptiveHistogramEqualization(const Mat &leftImage,const Mat &rightImage);

};

#endif // IMAGEALGORITHMVIEW_HPP
