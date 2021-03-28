#include "ImageSimilarityView.hpp"
#include "ui_ImageSimilarityView.h"

#include "imagealgorithm.hpp"

#include <QUrl>
#include <QDesktopServices>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QtConcurrent>
#include <QFuture>
#include <QMessageBox>

ImageSimilarityView::ImageSimilarityView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageSimilarityView)
{
    ui->setupUi(this);

    initUi();
}

ImageSimilarityView::~ImageSimilarityView()
{
    delete ui;
}

void ImageSimilarityView::initUi()
{
    this->setWindowTitle(tr("Image Similarity Discrimination And Processing System"));
    this->setWindowIcon( Awesome::getInstace()->icon( fa::image, Awesome::getInstace()->options) );

    // 按钮图标
    //    ui->action_file_open->setIcon( Awesome::getInstace()->icon( fa::folderopen, Awesome::getInstace()->options) );
    ui->ac_Save->setIcon( Awesome::getInstace()->icon( fa::save,  Awesome::getInstace()->options) );
    ui->ac_Histogram->setIcon( Awesome::getInstace()->icon( fa::areachart,  Awesome::getInstace()->options) );
    ui->ac_HistogramSub->setIcon( Awesome::getInstace()->icon( fa::barchart,  Awesome::getInstace()->options) );
    ui->ac_Exit->setIcon( Awesome::getInstace()->icon( fa::times,  Awesome::getInstace()->options) );
    ui->ac_About_Contents->setIcon( Awesome::getInstace()->icon( fa::alignleft,  Awesome::getInstace()->options) );
    ui->ac_About->setIcon( Awesome::getInstace()->icon( fa::exclamationcircle,  Awesome::getInstace()->options) );

    // 按钮提示
    ui->ac_Exit->setStatusTip(tr("Exit system."));
    ui->ac_Save->setStatusTip(tr("Save."));
    ui->ac_Histogram->setStatusTip(tr("Use histogram equalization to detect image similarity."));
    ui->ac_HistogramSub->setStatusTip(tr("Use aptive histogram equalization to detect image similarity."));
    ui->ac_About->setStatusTip(tr("About this software."));
    ui->ac_About_Contents->setStatusTip(tr("Software help page index."));

    // 背景
    Tool::setUiBackgroundColor(this, Awesome::getInstace()->getUiBackgroundColor());

    // 创建消息框
    m_MessageView = new MessageBoxView(ui->splitterBox);

    //    ui->splitterBox->setSizes(QList<int>({1, 1}));
    //    ui->splitterBox->setStretchFactor(0, 2);
    //    ui->splitterBox->setStretchFactor(1, 1);
    // TODO  上面这种方式不能实现效果 下面这种实现方式整理
    // https://stackoverflow.com/questions/43831474/how-to-equally-distribute-the-width-of-qsplitter
    ui->splitterBox->setStretchFactor(0,1);
    ui->splitterBox->setStretchFactor(1,1);
    ui->splitterBox->setSizes({static_cast<int>(10000 / 1.618), static_cast<int>(10000 - 10000 / 1.618)});

    // 创建图片框
    m_leftImage  = new ImageShowView(ui->splitterImage);
    m_rightImage  = new ImageShowView(ui->splitterImage);
    m_leftImage->getImage()->setImagePosition(ImageInfo::Left);
    m_rightImage->getImage()->setImagePosition(ImageInfo::Right);
    ui->splitterImage->setStretchFactor(0, 1);
    ui->splitterImage->setStretchFactor(1, 1);

    // DebugD
    m_DebugDisPlayController = new DebugDisPlayController(m_MessageView, this);
    m_DetectDisplayController = new DetectDisplayController(m_MessageView, m_leftImage->getImage(), m_rightImage->getImage(), this);

    // 算法实例
    m_ImageAlgorithm = new ImageAlgorithmView(this);

    connect(this, SIGNAL(debugMessageSig(QString)), m_MessageView, SLOT(debugMessage(QString)));
    connect(m_leftImage, SIGNAL(debugMessageSig(QString)), m_MessageView, SLOT(debugMessage(QString)));
    connect(m_rightImage, SIGNAL(debugMessageSig(QString)), m_MessageView, SLOT(debugMessage(QString)));
    connect(m_ImageAlgorithm, SIGNAL(debugMessageSig(QString)), m_MessageView, SLOT(debugMessage(QString)));

    connect(m_ImageAlgorithm, SIGNAL(detectMessageSig(QString)), m_MessageView, SLOT(detectMessage(QString)));

    // 更新project id
    connect(m_leftImage, SIGNAL(imageChangeSig()), this, SLOT(update()));
    connect(m_rightImage, SIGNAL(imageChangeSig()), this, SLOT(update()));
    connect(this, SIGNAL(projectIdSig(QString)), m_MessageView, SIGNAL(projectIdSig(QString)));

    update();
    debugMessage("Ui init ok !");
}

void ImageSimilarityView::debugMessage(QString message)
{
    QString objName = this->objectName();
    message = objName + QString("::") + message;
    emit(debugMessageSig(message));
}

void ImageSimilarityView::update()
{
    QString ProjectId;

    if (!m_leftImage->isLoadImage() || !m_rightImage->isLoadImage()){
        ProjectId = QString::number(0);
    }else{
        ProjectId = QString::number(QDateTime::currentMSecsSinceEpoch());
        m_MessageView->setProjectId(ProjectId);
    }

    m_HistogramFlag = false;

    emit(projectIdSig(ProjectId));
}

void ImageSimilarityView::on_ac_Save_triggered()
{
    if (!QFile::exists("Result")){
        QDir().mkdir("Result");
        debugMessage("Mkdir Result ok !");
    }
    if (!QFile::exists("ImageSimilarity.db")){
        debugMessage("ImageSimilarity.db not find !");
        return;
    }
    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch());
    // 毫秒级时间戳还原
    //QDateTime dateTime;
    //QString timestamp1 = dateTime.fromMSecsSinceEpoch(timestamp.toULongLong()).toString("yyyy-MM-dd hh-mm-ss-zzz");

    if (!QFile::exists(timestamp)){
        QtConcurrent::run([&timestamp](){
            QFile::copy(Tool::getDatabaseName(), QString("Result/") + timestamp + QString(".db"));
        });
        debugMessage(QString("Database ") + timestamp + QString(".db save ok !"));
        return;
    }
}

void ImageSimilarityView::on_ac_Histogram_triggered()
{

    if (m_HistogramFlag){
        QMessageBox::information(this, QString::fromLocal8Bit("Notice"),QString(tr("Histogram Images Similarity Is Complete !")));
        return;
    }
    m_HistogramFlag = true;
    QtConcurrent::run([=](){m_ImageAlgorithm->histogramImagesSimilarity( \
        m_leftImage->getImage()->getImageMat(), m_rightImage->getImage()->getImageMat());
        });
}

void ImageSimilarityView::on_ac_HistogramSub_triggered()
{

}

void ImageSimilarityView::on_ac_Exit_triggered()
{
    exit(0);
}

void ImageSimilarityView::on_ac_About_triggered()
{
    AboutView * about = new AboutView();
    about->setWindowFlags(about->windowFlags() | Qt::WindowStaysOnTopHint);
    about->show();
}

void ImageSimilarityView::on_ac_About_Contents_triggered()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/Seule-Seule/GraduationProjectImageSimilarity")));
}

void ImageSimilarityView::on_ac_Left_Histogram_triggered()
{
    m_ImageAlgorithm->CompImageHist(m_leftImage->getImage()->getImageMat(), ImageAlgorithmView::GRAY, nullptr, true);
    m_ImageAlgorithm->CompImageHist(m_leftImage->getImage()->getImageMat(), ImageAlgorithmView::RGB, nullptr, true);
    m_ImageAlgorithm->CompImageHist(m_leftImage->getImage()->getImageMat(), ImageAlgorithmView::HSV, nullptr, true);
}
