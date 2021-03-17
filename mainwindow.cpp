#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "imageshow.hpp"
#include "QtAwesome.h"

#include "QTextEdit"
#include "QSplitter"
#include "QLabel"
#include "QDebug"
#include "QFileDialog"

#include "opencv2/opencv.hpp"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtAwesome* awesome = new QtAwesome(this);
    awesome->initFontAwesome();
    QVariantMap options;
    options.insert( "color" , QColor(151,107,214) );

    this->setWindowTitle(tr("Image Similarity Discrimination And Processing System"));
    this->setWindowIcon( awesome->icon( fa::image, options) );

    // 图片框背景
    QPalette pal(ui->widget_image->palette());
    pal.setColor(QPalette::Background, QColor(81,15,173));
    ui->widget_image->setAutoFillBackground(true);
    ui->widget_image->setPalette(pal);

    // 消息框背景
    QPalette pal2(ui->widget_message->palette());
    pal2.setColor(QPalette::Background, QColor(151,107,214));
    ui->widget_message->setAutoFillBackground(true);
    ui->widget_message->setPalette(pal2);

    // icon
    ui->action_file_open->setIcon( awesome->icon( fa::folderopen, options) );
    ui->action_file_save->setIcon( awesome->icon( fa::save, options) );
    ui->action_op_his->setIcon( awesome->icon( fa::image, options) );
    ui->action_file_exit->setIcon( awesome->icon( fa::times, options) );
    ui->action_file_open->setStatusTip(tr("Open a image."));
    ui->action_file_exit->setStatusTip(tr("Exit system."));
    ui->action_file_save->setStatusTip(tr("Save."));

    // Separate left and right window for images.
    QHBoxLayout*    pHBox = new QHBoxLayout(ui->widget_image);
    pHBox->setContentsMargins(0, 0, 0, 0);

    QSplitter* leftRightSplitter = new QSplitter(Qt::Horizontal, ui->widget_image);
    m_leftImage     = new ImageShow(ui->widget_image);
    m_rightImage    = new ImageShow(ui->widget_image);
    leftRightSplitter->addWidget(m_leftImage);
    leftRightSplitter->addWidget(m_rightImage);
    leftRightSplitter->setStretchFactor(0, 1);
    leftRightSplitter->setStretchFactor(1, 1);
    pHBox->addWidget(leftRightSplitter);

    // button
    connect(ui->action_file_exit, SIGNAL(triggered()), this, SLOT(clickExitButton()));
    // connect(ui->action_file_open, SIGNAL(triggered()), this, SLOT(clickOpenButton()));
    connect(m_leftImage, SIGNAL(sendStatusBarMessageSig(QString, int)), this,
            SLOT(statusBurShowMessage(QString, int)));
    connect(m_rightImage, SIGNAL(sendStatusBarMessageSig(QString, int)), this,
            SLOT(statusBurShowMessage(QString, int)));

    QLabel* label = new QLabel(ui->widget_message);
    label->setText(QString("TODO: Message Box"));

//    Mat str = imread("Z:/graduationThesis/testImages/images/320x240/2019-07-17_Narrenmuehle_ZH-CN5582540867_320x240.jpg");
//    namedWindow("ss");
//    imshow("ss", str);
//    waitKey(0);
}

void MainWindow::clickExitButton()
{

    qDebug() << "Exit!";
    exit(0);
}

void MainWindow::clickOpenButton()
{

}

void MainWindow::statusBurShowMessage(QString message, int timeout)
{
    if (message.length() == 0 || timeout == 0){
        qDebug() << "Message is empty or timeout is zero!";
        return;
    }
    ui->statusbar->showMessage(message, timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

