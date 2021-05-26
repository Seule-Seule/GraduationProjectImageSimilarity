#ifndef IMAGESIMILARITYVIEW_HPP
#define IMAGESIMILARITYVIEW_HPP

#include <QMainWindow>

#include "Tools/awesome.hpp"
#include "Tools/tool.hpp"
#include "View/imageshowview.hpp"
#include "View/messageboxview.hpp"
#include "View/aboutview.hpp"
#include "View/imagealgorithmview.hpp"

#include "Controller/debugdisplaycontroller.hpp"
#include "Controller/detectdisplaycontroller.hpp"

#include <QSplitter>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

namespace Ui {
class ImageSimilarityView;
}

class ImageSimilarityView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageSimilarityView(QWidget *parent = nullptr);
    ~ImageSimilarityView();

signals:
    void debugMessageSig(QString);
    void projectIdSig(QString);


private:
    void initUi();
    void debugMessage(QString message);
    bool imageLoad();


private slots:
    void update();
    void on_ac_Save_triggered();
    void on_ac_Histogram_triggered();
    void on_ac_HistogramSub_triggered();
    void on_ac_Exit_triggered();
    void on_ac_About_triggered();
    void on_ac_About_Contents_triggered();
    void on_ac_Left_Histogram_triggered();
    void on_ac_Right_Histogram_triggered();
    void on_ac_Calculate_triggered();
    void on_ac_Sub_Normal_CHist_triggered();
    void on_ac_SIFT_triggered();
    void on_ac_aHash_triggered();
    void on_ac_pHash_triggered();
    void on_ac_dHash_triggered();

private:
    Ui::ImageSimilarityView *ui;
    PropertyBuilderByName(bool, HistogramFlag, private);
    PropertyBuilderByName(bool, NormalHistogramFlag, private);
    PropertyBuilderByName(bool, SubHistogramFlag, private);

    PropertyBuilderByName(bool, SIFTFlag, private);

    PropertyBuilderByName(bool, aHashFlag, private);
    PropertyBuilderByName(bool, pHashFlag, private);
    PropertyBuilderByName(bool, dHashFlag, private);

    PropertyBuilderByName(bool, CalculateFlag, private);

    PointerPropertyBuilderByName(ImageShowView, leftImage, private);
    PointerPropertyBuilderByName(ImageShowView, rightImage, private);
    PointerPropertyBuilderByName(MessageBoxView, MessageView, private);
    PointerPropertyBuilderByName(ImageAlgorithmView, ImageAlgorithm, private);

    PointerPropertyBuilderByName(DebugDisPlayController, DebugDisPlayController, private);
    PointerPropertyBuilderByName(DetectDisplayController, DetectDisplayController, private);
};

#endif // IMAGESIMILARITYVIEW_HPP
