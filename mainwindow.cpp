#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "imageshow.hpp"
#include "QtAwesome.h"

#include "QTextEdit"
#include "QSplitter"
#include "QLabel"

#include "opencv2/opencv.hpp"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtAwesome* awesome = new QtAwesome(this);
    awesome->initFontAwesome();

    // icon
    ui->action_file_new->setIcon( awesome->icon( fa::folderopen) );
    ui->action_file_save->setIcon( awesome->icon( fa::save) );
    ui->action_op_his->setIcon( awesome->icon( fa::image) );

    // Separate left and right window for images.
    QHBoxLayout* pHBox = new QHBoxLayout(ui->widget_image);
    pHBox->setContentsMargins(0, 0, 0, 0);
    QSplitter* leftRightSplitter = new QSplitter(Qt::Horizontal, ui->widget_image);
    ImageShow* leftImage = new ImageShow(ui->widget_image);
    ImageShow* RightImage = new ImageShow(ui->widget_image);
    leftRightSplitter->addWidget(leftImage);
    leftRightSplitter->addWidget(RightImage);
    leftRightSplitter->setStretchFactor(0, 1);
    leftRightSplitter->setStretchFactor(1, 1);
    pHBox->addWidget(leftRightSplitter);

    QLabel* label = new QLabel(ui->widget_message);
    label->setText(QString("TODO: Message Box"));

//    Mat str = imread("Z:/graduationThesis/testImages/images/320x240/2019-07-17_Narrenmuehle_ZH-CN5582540867_320x240.jpg");
//    namedWindow("ss");
//    imshow("ss", str);
//    waitKey(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

