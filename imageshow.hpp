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

public:
    void debugShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout);

signals:
    void sendStatusBarMessageSig(QString message, int timeout);
    void sendDebugMessageSig(QString message);

private:
    QImage  cvMatToQImage( const cv::Mat &inMat );
    QVector<QString> splitQString(const QString &str, const QString &pattern);
private:
    void  initUi();
public :
    void  setPathIm();
    void  setShowIm();

public slots:
    void  clickOpenImButton();
    void  clickUnloadImButton();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ImageShow *ui;

public:
    enum Position{
        left,
        right
    };

private:
    PropertyBuilderByName(QString, imageId, private);
    PropertyBuilderByName(QString, imageName, private);
    PropertyBuilderByName(QString, imagePath, private);
    PropertyBuilderByName(QSize, imageSize, private);
    PropertyBuilderByName(Mat, matImage, private);
    PropertyBuilderByName(QImage, qImage, private);
    PropertyBuilderByName(Position, position, private);

};

#endif // IMAGESHOW_HPP
