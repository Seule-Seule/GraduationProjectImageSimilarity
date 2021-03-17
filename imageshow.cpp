#define _CRT_SECURE_NO_WARNINGS

#include "imageshow.hpp"
#include "subimagewindow.hpp"

#include "QtAwesome.h"

#include "ui_imageshow.h"
#include "QDebug"
#include "qfiledialog.h"
#include "qfontmetrics.h"

#include "opencv2/opencv.hpp"

using namespace cv;

ImageShow::ImageShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageShow)
{
    ui->setupUi(this);

    QtAwesome* awesome = new QtAwesome(this);
    awesome->initFontAwesome();
    QVariantMap options;
    options.insert( "color" , QColor(255,230,0) );

    // icon

    ui->button_history_im->setFlat(true);
    ui->button_open_im->setFlat(true);
    ui->button_load_im->setFlat(true);
    ui->button_open_im->setIcon( awesome->icon( fa::folderopen, options) );
    ui->button_load_im->setIcon( awesome->icon( fa::spinner, options) );
    ui->button_history_im->setIcon(awesome->icon( fa::chevrondown, options));
    ui->label_path_im->setText(QString(""));

    // button
    connect(ui->button_open_im, SIGNAL(clicked()), this, SLOT(clickOpenImButton()));

    // 图片显示区域
    m_imageLabel = new QLabel(ui->mdiArea_show_im);
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

void ImageShow::clickOpenImButton()
{

    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("open a image."),
                                                    "D:/",
                                                    tr("images(*.png *.jpg *.jpeg *.bmp)"));
    if (filePath.length() == 0){
        qDebug() << "No file selected!";
        emit(sendStatusBarMessageSig(tr("No file selected!"), 3000));
        return;
    }
    m_matImage = imread(filePath.toStdString());
    if (m_matImage.empty()){
        qDebug() << "File " << filePath << " open fail!";
        emit(sendStatusBarMessageSig(tr("Image load fail!"), 3000));
        return;
    }

    m_imagePath = filePath;
    QVector<QString> _imagePathVector = splitQString(filePath, "/");
    m_imageName = _imagePathVector.back();

    QVector<QString> _imageNameVector = splitQString(m_imageName, ".");
    m_imageId = _imageNameVector[0];
    m_qImage = cvMatToQImage(m_matImage);

    setPathIm();
    //SubImageWindow * imagewin = new SubImageWindow(&m_qImage);
    //ui->mdiArea_show_im->addSubWindow(imagewin)->resize(300,300);
}

void  ImageShow::setPathIm()
{
    QFontMetrics fontWidth(ui->label_path_im->font());//得到每个字符的宽度
    QString elideNote = fontWidth.elidedText(m_imagePath, Qt::ElideMiddle, ui->label_path_im->width());//填满整个label
    ui->label_path_im->setText(elideNote);//显示省略好的字符串
    ui->label_path_im->setToolTip(m_imagePath);//设置tooltips
    ui->label_path_im->setStyleSheet("background-color: rgb(151,107,214);color:rgb(255,241,115)");
}

void ImageShow::resizeEvent(QResizeEvent *event)
{
    setPathIm();

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
