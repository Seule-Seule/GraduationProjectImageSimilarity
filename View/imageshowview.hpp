#ifndef IMAGESHOWVIEW_HPP
#define IMAGESHOWVIEW_HPP

#include <QWidget>

#include "Model/basemodel.hpp"
#include "Tools/awesome.hpp"
#include "Tools/tool.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

namespace Ui {
class ImageShowView;
}

class ImageInfo
{
public:
    enum Position{
        Left,
        Right
    };

    PropertyBuilderByName(QString, ImagePath, private);
    PropertyBuilderByName(QString, ImageName, private);
    PropertyBuilderByName(QImage, ImageQImage, private);
    PropertyBuilderByName(Mat, ImageMat, private);
    PropertyBuilderByName(size_t, ImagePosition, private);
};


class ImageShowView : public QWidget
{
    Q_OBJECT

public:
    explicit ImageShowView(QWidget *parent = nullptr);
    ~ImageShowView();

signals:
    void debugMessageSig(QString);

private:
    void initUi();
    QImage cvMatToQImage( const cv::Mat &inMat );
    void setPathIm();
    void setShowIm();
    int imageClear();

public:
    bool isLoadImage();
    void update();

private slots:
    void debugMessage(QString message);
    void on_Btn_Load_clicked();
    void on_Btn_Unload_clicked();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ImageShowView *ui;
    PointerPropertyBuilderByName(ImageInfo, Image, private);
};

#endif // IMAGESHOWVIEW_HPP
