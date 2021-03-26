#ifndef IMAGESIMILARITYVIEW_HPP
#define IMAGESIMILARITYVIEW_HPP

#include <QMainWindow>

#include "Tools/awesome.hpp"
#include "Tools/tool.hpp"
#include "View/baseview.hpp"
#include "View/imageshowview.hpp"
#include "View/messageboxview.hpp"
#include "View/aboutview.hpp"
#include "View/imagealgorithmview.hpp"

#include "Controller/debugdisplaycontroller.hpp"

#include <QSplitter>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

namespace Ui {
class ImageSimilarityView;
}

class ImageSimilarityView : public QMainWindow, public BaseView
{
    Q_OBJECT

public:
    explicit ImageSimilarityView(QWidget *parent = nullptr);
    ~ImageSimilarityView();

signals:
    void debugMessageSig(QString);

private:
    void initUi();
    void debugMessage(QString message);

public:
    virtual void update();

private slots:
    void on_ac_Save_triggered();
    void on_ac_Histogram_triggered();
    void on_ac_HistogramSub_triggered();
    void on_ac_Exit_triggered();
    void on_ac_About_triggered();
    void on_ac_About_Contents_triggered();

private:
    Ui::ImageSimilarityView *ui;
    PointerPropertyBuilderByName(ImageShowView, leftImage, private);
    PointerPropertyBuilderByName(ImageShowView, rightImage, private);
    PointerPropertyBuilderByName(MessageBoxView, MessageView, private);
        PointerPropertyBuilderByName(ImageAlgorithmView, ImageAlgorithm, private);

    PointerPropertyBuilderByName(DebugDisPlayController, DebugDisPlayController, private);

};

#endif // IMAGESIMILARITYVIEW_HPP
