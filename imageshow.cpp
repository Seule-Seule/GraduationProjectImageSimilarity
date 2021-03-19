#define _CRT_SECURE_NO_WARNINGS

#include "imageshow.hpp"
#include "awesome.hpp"

#include "ui_imageshow.h"
#include "QDebug"
#include "QFiledialog"
#include "QFontmetrics"
#include "QLineEdit"

#include "opencv2/opencv.hpp"

using namespace cv;

ImageShow::ImageShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageShow)
{
    ui->setupUi(this);

    initUi();

    // 按钮功能
    connect(ui->button_open_im, SIGNAL(clicked()), this, SLOT(clickOpenImButton()));
    connect(ui->button_unload_im, SIGNAL(clicked()), this, SLOT(clickUnloadImButton()));
}

void  ImageShow::initUi()
{
    // icon
    ui->button_open_im->setFlat(true);
    ui->button_unload_im->setFlat(true);
    ui->button_history_im->setFlat(true);
    ui->button_open_im->setIcon( Awesome::getInstace()->icon( fa::folderopen, Awesome::getInstace()->options) );
    ui->button_unload_im->setIcon( Awesome::getInstace()->icon( fa::share, Awesome::getInstace()->options) );
    ui->button_history_im->setIcon( Awesome::getInstace()->icon( fa::chevrondown, Awesome::getInstace()->options) );
    ui->button_open_im->setStatusTip(tr("Open image !"));
    ui->button_unload_im->setStatusTip(tr("Unload image !"));
    ui->button_history_im->setStatusTip(tr("Show open image history !"));

    // 图片显示区域
    ui->label_show_im->setText(QString(""));
    ui->label_show_im->setScaledContents(true);
    ui->label_show_im->setAlignment(Qt::AlignCenter);

    // 图片框背景
    QPalette pal(ui->label_show_im->palette());
    pal.setColor(QPalette::Background, QColor(204,204,204));
    ui->label_show_im->setAutoFillBackground(true);
    ui->label_show_im->setPalette(pal);

    // 路径框背景
    QPalette pal1(ui->label_path_im->palette());
    pal1.setColor(QPalette::Background, QColor(255, 255, 255));
    ui->label_path_im->setAutoFillBackground(true);
    ui->label_path_im->setPalette(pal1);
}

QVector<QString> ImageShow::splitQString(const QString &str, const QString &pattern)
{
    char * strc = new char[strlen(str.toStdString().c_str())+1];
    strcpy(strc, str.toStdString().c_str());   //string转换成C-string
    QVector<QString> res;
    char* temp = strtok(strc, pattern.toStdString().c_str());
    while(temp != NULL)
    {
        res.push_back(QString(temp));
        temp = strtok(NULL, pattern.toStdString().c_str());
    }
    delete[] strc;
    return res;
}

void ImageShow::debugShowMessage(QString message)
{
    if (m_position == ImageShow::left){
        message = QString("Left Image: ") + message;
    }
    else {
        message = QString("Right Image: ") + message;
    }
    emit(sendDebugMessageSig(message));
}

void ImageShow::statusBurShowMessage(QString message, int timeout)
{
    emit(sendStatusBarMessageSig(message, timeout));
}

void ImageShow::clickOpenImButton()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("open a image."),
                                                    "D:/",
                                                    tr("images(*.png *.jpg *.jpeg *.bmp)"));
    if (filePath.length() == 0){
        statusBurShowMessage(tr("No file selected!"), 3000);
        return;
    }
    m_matImage = imread(filePath.toStdString());
    if (m_matImage.empty()){
        statusBurShowMessage(tr("Image load fail!"), 3000);
        return;
    }

    m_imagePath = filePath;
    QVector<QString> _imagePathVector = splitQString(filePath, "/");
    m_imageName = _imagePathVector.back();

    QVector<QString> _imageNameVector = splitQString(m_imageName, ".");
    m_imageId = _imageNameVector[0];
    m_qImage = cvMatToQImage(m_matImage);

    setPathIm();
    setShowIm();
    statusBurShowMessage(tr("Image load ok !"), 3000);
}

void  ImageShow::clickUnloadImButton()
{
    // unload image.
    if (m_matImage.empty()){
        statusBurShowMessage(tr("No image need unload !"), 3000);
        return;
    }

    m_matImage.release();
    m_imagePath.clear();
    m_imageName.clear();
    m_imageId.clear();
    setPathIm();
    setShowIm();
    statusBurShowMessage(tr("Image unload ok !"), 3000);
}

void  ImageShow::setPathIm()
{
    QFontMetrics fontWidth(ui->label_path_im->font());
    QString elideNote = fontWidth.elidedText(m_imagePath, Qt::ElideMiddle, ui->label_path_im->width());
    ui->label_path_im->setText(elideNote);
    ui->label_path_im->setToolTip(m_imagePath);
}

void  ImageShow::setShowIm()
{
    if (m_matImage.empty()){
        ui->label_show_im->clear();
        return;
    }
    ui->label_show_im->setPixmap(QPixmap::fromImage(m_qImage.scaled(ui->label_show_im->size().width(),ui->label_show_im->size().height(),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

void ImageShow::resizeEvent(QResizeEvent *event)
{
    setPathIm();
    setShowIm();
}

QImage ImageShow::cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable( 256, qRgb(0,0,0) );
        // only create our color table the first time.
        if ( sColorTable[255] == qRgb(0,0,0) )
        {
            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );

        return image;
    }

    default:
        qWarning() << "cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}


ImageShow::~ImageShow()
{
    delete ui;
}
