#include "imageshowview.hpp"
#include "ui_imageshowview.h"

#include <QFileDialog>

ImageShowView::ImageShowView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageShowView)
{
    ui->setupUi(this);

    initUi();
}

ImageShowView::~ImageShowView()
{
    delete ui;
}

void ImageShowView::initUi()
{
    // icon
    ui->Btn_Load->setFlat(true);
    ui->Btn_Unload->setFlat(true);
    ui->Btn_History->setFlat(true);
    ui->Btn_Load->setIcon( Awesome::getInstace()->icon( fa::folderopen, Awesome::getInstace()->options) );
    ui->Btn_Unload->setIcon( Awesome::getInstace()->icon( fa::share, Awesome::getInstace()->options) );
    ui->Btn_History->setIcon( Awesome::getInstace()->icon( fa::chevrondown, Awesome::getInstace()->options) );
    ui->Btn_Load->setStatusTip(tr("Open image !"));
    ui->Btn_Unload->setStatusTip(tr("Unload image !"));
    ui->Btn_History->setStatusTip(tr("Show open image history !"));

    Tool::setUiElementColor(this, Awesome::getInstace()->getUiBackgroundColor());

    // 图片显示区域
    ui->lb_Show->setText(QString(""));
    ui->lb_Show->setScaledContents(true);
    ui->lb_Show->setAlignment(Qt::AlignCenter);

    // 背景
    Tool::setUiBackgroundColor(this, Awesome::getInstace()->getUiBackgroundColor());

    // 图片显示区域背景
    Tool::setUiBackgroundColor(ui->lb_Show, QColor(204,204,204));

    // 路径框背景
    Tool::setUiBackgroundColor(ui->lb_Path, QColor(255, 255, 255));

    m_Image = new ImageInfo();
}

int ImageShowView::imageClear()
{
    if (m_Image->getImageMat().empty()){
        debugMessage("Image is empty !");
        return -1;
    }

    m_Image->setImageMat(Mat());
    m_Image->setImageQImage(QImage());
    m_Image->setImageName(QString());
    m_Image->setImagePath(QString());
    return 0;
}

void ImageShowView::update()
{

}

void ImageShowView::debugMessage(QString message)
{
    QString objName = this->objectName();
    message = objName + QString("::") + message;
    emit(debugMessageSig(message));
}

void ImageShowView::resizeEvent(QResizeEvent *event)
{
    setPathIm();
}

void ImageShowView::on_Btn_Load_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("open a image."),
                                                    "D:/",
                                                    tr("images(*.png *.jpg *.jpeg *.bmp)"));
    if (filePath.length() == 0){
        debugMessage("No file selected!");
        return;
    }
    m_Image->setImageMat(imread(filePath.toStdString()));
    if (m_Image->getImageMat().empty()){
        debugMessage( "Image load fail!");
        return;
    }

    m_Image->setImagePath(filePath);
    QVector<QString> _imagePathVector = Tool::splitQString(filePath, "/");
    m_Image->setImageName(_imagePathVector.back());

    m_Image->setImageQImage(cvMatToQImage(m_Image->getImageMat()));

    setPathIm();
    setShowIm();
    debugMessage("Image load ok !");
}

void ImageShowView::setPathIm()
{
    QFontMetrics fontWidth(ui->lb_Path->font());
    QString elideNote = fontWidth.elidedText(m_Image->getImagePath(), Qt::ElideMiddle, ui->lb_Path->width()-20);
    ui->lb_Path->setText(elideNote);
    ui->lb_Path->setToolTip(m_Image->getImagePath());
}

void ImageShowView::setShowIm()
{
    if (m_Image->getImageMat().empty()){
        ui->lb_Show->clear();
        return;
    }
    QPixmap qPixmap = QPixmap::fromImage(m_Image->getImageQImage().scaled(ui->lb_Show->size().width(),ui->lb_Show->size().height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lb_Show->setPixmap(qPixmap);
}

QImage ImageShowView::cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image( inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step), QImage::Format_ARGB32 );

            return image;
        }

            // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image( inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_RGB888 );

            return image.rgbSwapped();
        }

            // 8-bit, 1 channel
        case CV_8UC1:
        {
            static QVector<QRgb>  sColorTable( 256, qRgb(0,0,0) );
            // only create our color table the first time.
            if ( sColorTable[255] == qRgb(0,0,0) ){
                for ( int i = 0; i < 256; ++i )
                {
                    sColorTable[i] = qRgb( i, i, i );
                }
            }
            QImage image( inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_Indexed8 );
            image.setColorTable( sColorTable );

            return image;
        }
        default:
            debugMessage(QString("cvMatToQImage() - cv::Mat image type not handled in switch:") + inMat.type() );
            break;
    }

    return QImage();
}

void ImageShowView::on_Btn_Unload_clicked()
{
    int temp = imageClear();
    if (0 != temp){
        debugMessage(QString("Image unload fail, error code is ") + QString::number(temp));
        return;
    }
    setPathIm();
    setShowIm();
    debugMessage("Image unload success");
}
