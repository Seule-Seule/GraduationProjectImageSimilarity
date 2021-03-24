#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "imageshow.hpp"
#include "awesome.hpp"
#include "imagealgorithm.hpp"
#include "aboutimagesimilarity.hpp"

#include "QTextEdit"
#include "QSplitter"
#include "QLabel"
#include "QDebug"
#include "QFileDialog"
#include "QDateTime"
#include <QDesktopServices>

#include "opencv2/opencv.hpp"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUi();
    initConnect();
}


void MainWindow::initConnect()
{
    // 图片显示框向状态栏推送通知
    connect(m_leftImage, SIGNAL(sendStatusBarMessageSig(QString, int)), this,SLOT(statusBurShowMessage(QString, int)));
    connect(m_rightImage, SIGNAL(sendStatusBarMessageSig(QString, int)), this,SLOT(statusBurShowMessage(QString, int)));

    // 消息框向状态栏推送通知
    connect(m_messageOperate, SIGNAL(sendStatusBarMessageSig(QString, int)), this,SLOT(statusBurShowMessage(QString, int)));

    // filesave
    connect(m_fileSave, SIGNAL(sendStatusBarMessageSig(QString, int)), this, SLOT(statusBurShowMessage(QString, int)));

    // 算法向状态栏推送消息
    connect(m_imageAlgorithm, SIGNAL(sendStatusBarMessageSig(QString, int)), this,SLOT(statusBurShowMessage(QString, int)));

    // 图片框向消息框推送消息
    connect(m_leftImage, SIGNAL(sendDebugMessageSig(QString)), this, SLOT(debugShowMessage(QString)));
    connect(m_rightImage, SIGNAL(sendDebugMessageSig(QString)), this, SLOT(debugShowMessage(QString)));

    // 算法向消息框推送消息
    connect(m_imageAlgorithm, SIGNAL(sendDebugMessageSig(QString)), this, SLOT(debugShowMessage(QString)));
    connect(m_imageAlgorithm, SIGNAL(sendDetectMessageSig(QString)), m_messageOperate, SLOT(detectShowMessage(QString)));

    // filesave
    connect(m_fileSave, SIGNAL(sendDebugMessageSig(QString)), this, SLOT(debugShowMessage(QString)));

}

void MainWindow::initUi()
{
    this->setWindowTitle(tr("Image Similarity Discrimination And Processing System"));
    this->setWindowIcon( Awesome::getInstace()->icon( fa::image, Awesome::getInstace()->options) );

    // 按钮图标
//    ui->action_file_open->setIcon( Awesome::getInstace()->icon( fa::folderopen, Awesome::getInstace()->options) );
    ui->action_file_save->setIcon( Awesome::getInstace()->icon( fa::save,  Awesome::getInstace()->options) );
    ui->action_op_his->setIcon( Awesome::getInstace()->icon( fa::areachart,  Awesome::getInstace()->options) );
    ui->action_op_his_sub->setIcon( Awesome::getInstace()->icon( fa::barchart,  Awesome::getInstace()->options) );
    ui->action_file_exit->setIcon( Awesome::getInstace()->icon( fa::times,  Awesome::getInstace()->options) );
    ui->action_help_content->setIcon( Awesome::getInstace()->icon( fa::alignleft,  Awesome::getInstace()->options) );
    ui->action_about->setIcon( Awesome::getInstace()->icon( fa::exclamationcircle,  Awesome::getInstace()->options) );

    // 按钮提示
//    ui->action_file_open->setStatusTip(tr("Open a project."));
    ui->action_file_exit->setStatusTip(tr("Exit system."));
    ui->action_file_save->setStatusTip(tr("Save."));
    ui->action_op_his->setStatusTip(tr("Use histogram equalization to detect image similarity."));
    ui->action_op_his->setStatusTip(tr("Use aptive histogram equalization to detect image similarity."));
    ui->action_about->setStatusTip(tr("About this software."));
    ui->action_help_content->setStatusTip(tr("Software help page index."));

    // 图片框背景
    QPalette pal(ui->widget->palette());
    pal.setColor(QPalette::Background, QColor(214,236,240));
    ui->widget->setAutoFillBackground(true);
    ui->widget->setPalette(pal);


    QVBoxLayout*    pVBox = new QVBoxLayout(ui->widget);
    pVBox->setContentsMargins(0, 0, 0, 0);
    ui->widget->setContentsMargins(0, 0, 0, 0);

    // 创建图片框
    QSplitter* leftRightSplitter = new QSplitter(Qt::Horizontal, ui->widget);
    leftRightSplitter->setContentsMargins(0,0,0,0);
    m_leftImage     = new ImageShow(ui->widget);
    m_rightImage    = new ImageShow(ui->widget);
    m_leftImage->setposition(ImageShow::left);
    m_rightImage->setposition(ImageShow::right);
    leftRightSplitter->addWidget(m_leftImage);
    leftRightSplitter->addWidget(m_rightImage);
    leftRightSplitter->setStretchFactor(0, 1);
    leftRightSplitter->setStretchFactor(1, 1);

    // 创建消息框
    m_messageOperate = new MessageOperate(ui->widget);
    m_messageOperate->setMaximumHeight(this->size().height()*1/3);

    pVBox->addWidget(leftRightSplitter);
    pVBox->addWidget(m_messageOperate);

    // 算法实例
    m_imageAlgorithm = new ImageAlgorithm(this);

    // 保存文件
    m_fileSave = new FileSave(this);

    debugShowMessage("Ui init ok !");
}

void MainWindow::debugShowMessage(QString message)
{
    m_messageOperate->debugShowMessage(message);
}

void MainWindow::statusBurShowMessage(QString message, int timeout, bool selfUse)
{
    if (message.length() == 0 || timeout == 0){
        debugShowMessage("Message is empty or timeout is zero!");
        return;
    }
    if (selfUse){
        debugShowMessage(message);
    }
    ui->statusbar->showMessage(message, timeout);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_about_triggered()
{
    AboutImageSimilarity * about = new AboutImageSimilarity();
    about->show();
}

void MainWindow::on_action_help_content_triggered()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/Seule-Seule")));
}

void MainWindow::on_action_file_exit_triggered()
{
    debugShowMessage("Exit system !");
    exit(0);
}

void MainWindow::on_action_file_save_triggered()
{
    //m_fileSave->save(*(m_messageOperate->m_detectModel), m_leftImage->getqPixmap(), m_rightImage->getqPixmap());
}

void MainWindow::on_action_op_his_triggered()
{
    if (m_leftImage->getmatImage().empty()){
        statusBurShowMessage(tr("Left image not load !"), 3000, this);
        return;
    }
    if (m_rightImage->getmatImage().empty()){
        statusBurShowMessage(tr("Right image not load !"), 3000, this);
        return;
    }
    m_imageAlgorithm->histogramImagesSimilarity(m_leftImage->getmatImage(), m_rightImage->getmatImage());
}
