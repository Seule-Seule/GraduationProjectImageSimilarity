#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "imageshow.hpp"
#include "QtAwesome.h"

#include "QTextEdit"
#include "QSplitter"
#include "QLabel"
#include "QDebug"
#include "QFileDialog"
#include "QDateTime"

#include "opencv2/opencv.hpp"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    initModel();
    initUi();
    initConnect();
}


void MainWindow::initConnect()
{
    // 按钮功能
    connect(ui->action_file_exit, SIGNAL(triggered()), this, SLOT(clickExitButton()));
    connect(ui->btn_message_status, SIGNAL(clicked()), this, SLOT(clickMessageStatusBtn()));

    // 消息框状态切换
    connect(ui->btn_msg_debug, &QPushButton::clicked, [&](){
        if ( !messageHide ){
            ui->widget_message->show();
            ui->btn_message_status->setIcon( m_iconAwesome->icon( fa::chevroncircledown, m_iocnOptions) );
            messageHide = true;
        }
        ui->stackedWidget->setCurrentWidget(ui->page_msg_debug);
                    });
    connect(ui->btn_msg_message, &QPushButton::clicked, [&](){
        if ( !messageHide ){
            ui->widget_message->show();
            ui->btn_message_status->setIcon( m_iconAwesome->icon( fa::chevroncircledown, m_iocnOptions) );
            messageHide = true;
        }
        ui->stackedWidget->setCurrentWidget(ui->page_msg_test);
                    });

    // 图片显示框向状态栏推送通知
    connect(m_leftImage, SIGNAL(sendStatusBarMessageSig(QString, int)), this,
            SLOT(statusBurShowMessage(QString, int)));
    connect(m_rightImage, SIGNAL(sendStatusBarMessageSig(QString, int)), this,
            SLOT(statusBurShowMessage(QString, int)));

    // 图片显示框向消息框推送消息
    connect(m_leftImage, SIGNAL(sendDebugMessageSig(QString)), this, SLOT(debugShowMessage(QString)));
    connect(m_rightImage, SIGNAL(sendDebugMessageSig(QString)), this, SLOT(debugShowMessage(QString)));
    debugShowMessage("All connect complate !");
}

void MainWindow::initModel()
{
    m_debugListModel = new QStringListModel(this);
    ui->listView_debug->setModel(m_debugListModel);
    ui->listView_debug->setEditTriggers(QAbstractItemView:: NoEditTriggers);

    debugShowMessage("Medol and view init ok !");
}

void MainWindow::initUi()
{
    m_iconAwesome = new QtAwesome(this);
    m_iconAwesome->initFontAwesome();
    m_iocnOptions.insert( "color" , QColor(176,124,227) );

    this->setWindowTitle(tr("Image Similarity Discrimination And Processing System"));
    this->setWindowIcon( m_iconAwesome->icon( fa::image, m_iocnOptions) );

    // 按钮图标
    ui->action_file_open->setIcon( m_iconAwesome->icon( fa::folderopen, m_iocnOptions) );
    ui->action_file_save->setIcon( m_iconAwesome->icon( fa::save, m_iocnOptions) );
    ui->action_op_his->setIcon( m_iconAwesome->icon( fa::image, m_iocnOptions) );
    ui->action_file_exit->setIcon( m_iconAwesome->icon( fa::times, m_iocnOptions) );

    // 按钮提示
    ui->action_file_open->setStatusTip(tr("Open a project."));
    ui->action_file_exit->setStatusTip(tr("Exit system."));
    ui->action_file_save->setStatusTip(tr("Save."));
    ui->action_op_his->setStatusTip(tr("Use histogram to detect image similarity."));

    // 图片框背景
    QPalette pal(ui->widget_image->palette());
    pal.setColor(QPalette::Background, QColor(214,236,240));
    ui->widget_image->setAutoFillBackground(true);
    ui->widget_image->setPalette(pal);

    // 消息框
    ui->btn_message_status->setIcon( m_iconAwesome->icon( fa::chevroncircledown, m_iocnOptions) );
    ui->btn_message_status->setFlat(true);
    ui->btn_message_status->setStatusTip(tr("Show or close the message box!"));
    ui->btn_msg_debug->setFlat(true);
    ui->btn_msg_debug->setStatusTip(tr("Show debug message in message box!"));
    ui->btn_msg_message->setFlat(true);
    ui->btn_msg_message->setStatusTip(tr("Show image similarity message in message box!"));
    messageHide = true;

    // 创建图片框
    QHBoxLayout*    pHBox = new QHBoxLayout(ui->widget_image);
    pHBox->setContentsMargins(0, 0, 0, 0);
    QSplitter* leftRightSplitter = new QSplitter(Qt::Horizontal, ui->widget_image);
    leftRightSplitter->setContentsMargins(0,0,0,0);
    m_leftImage     = new ImageShow(ui->widget_image);
    m_rightImage    = new ImageShow(ui->widget_image);
    m_leftImage->setposition(ImageShow::left);
    m_rightImage->setposition(ImageShow::right);
    leftRightSplitter->addWidget(m_leftImage);
    leftRightSplitter->addWidget(m_rightImage);
    leftRightSplitter->setStretchFactor(0, 1);
    leftRightSplitter->setStretchFactor(1, 1);
    pHBox->addWidget(leftRightSplitter);

    debugShowMessage("Ui init ok !");
}

void MainWindow::clickExitButton()
{
    debugShowMessage("Exit system !");
    exit(0);
}

void MainWindow::clickOpenButton()
{

}

void MainWindow::clickMessageStatusBtn()
{
    if ( messageHide ){
        ui->widget_message->close();
        ui->btn_message_status->setIcon( m_iconAwesome->icon( fa::chevroncircleup, m_iocnOptions) );
        messageHide = false;
    }
    else{
        ui->widget_message->show();
        ui->btn_message_status->setIcon( m_iconAwesome->icon( fa::chevroncircledown, m_iocnOptions) );
        messageHide = true;
    }
}

void MainWindow::debugShowMessage(QString message)
{
    if (message.isEmpty())
        return;
    QDateTime _currentDateTime =QDateTime::currentDateTime();
    QString _currentTime =_currentDateTime.toString("[ yyyy-MM-dd hh:mm:ss.zzz ]  ");
    message = _currentTime + message;
    m_debugListModel->insertRow(m_debugListModel->rowCount());
    QModelIndex index = m_debugListModel->index(m_debugListModel->rowCount()-1,0);
    m_debugListModel->setData(index, message, Qt::DisplayRole);
    qDebug() << message;
}

void MainWindow::statusBurShowMessage(QString message, int timeout)
{
    if (message.length() == 0 || timeout == 0){
        debugShowMessage(tr("Message is empty or timeout is zero!"));
        return;
    }
    ui->statusbar->showMessage(message, timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

