#ifndef IMAGESHOW_HPP
#define IMAGESHOW_HPP

#include "value.hpp"

#include <QWidget>
#include "QLabel"

#include "opencv2/opencv.hpp"

using namespace cv;

namespace Ui {
class ImageShow;
}


class ImageShow : public QWidget
{
    Q_OBJECT

public:
    explicit ImageShow(QWidget *parent = nullptr);
    ~ImageShow();

signals:
    void sendStatusBarMessageSig(QString message, int timeout);

private:
    QImage  cvMatToQImage( const cv::Mat &inMat );
    QVector<QString> splitQString(const QString &str, const QString &pattern);

public :
    void  setPathIm();
    void    openImage(QString imagePath);

public slots:
    void  clickOpenImButton();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ImageShow *ui;

private:
    PointerPropertyBuilderByName(QLabel, imageLabel, private);
    PropertyBuilderByName(QString, imageId, private);
    PropertyBuilderByName(QString, imageName, private);
    PropertyBuilderByName(QString, imagePath, private);
    PropertyBuilderByName(QSize, imageSize, private);
    PropertyBuilderByName(Mat, matImage, private);
    PropertyBuilderByName(QImage, qImage, private);
};

#endif // IMAGESHOW_HPP
