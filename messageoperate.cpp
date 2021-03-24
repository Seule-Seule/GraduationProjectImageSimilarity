#include "messageoperate.hpp"
#include "ui_messageoperate.h"

#include "awesome.hpp"
#include "tool.hpp"

#include <QDebug>
#include <QDateTime>
#include <QSqlError>

MessageOperate::MessageOperate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageOperate)
{
    ui->setupUi(this);


    initUi();
    initConnect();


    // 消息框 Debug 栏
//    m_debugListModel = new QStringListModel(this);
//    ui->listView_debug->setModel(m_debugListModel);
//    ui->listView_debug->setEditTriggers(QAbstractItemView:: NoEditTriggers);


    // 消息框 Message 栏
//    m_detectListModel = new QStringListModel(this);
//    ui->listView_detect->setModel(m_detectListModel);
//    ui->listView_detect->setEditTriggers(QAbstractItemView:: NoEditTriggers);


}

void MessageOperate::initUi()
{
    // 消息框
    ui->btn_message_status->setIcon( Awesome::getInstace()->icon( fa::chevroncircledown, Awesome::getInstace()->options) );
    ui->btn_message_status->setFlat(true);
    ui->btn_message_status->setStatusTip(tr("Show or close the message box!"));
    ui->btn_msg_debug->setFlat(true);
    ui->btn_msg_debug->setStatusTip(tr("Show debug message in message box!"));
    ui->btn_msg_message->setFlat(true);
    ui->btn_msg_message->setStatusTip(tr("Show image similarity message in message box!"));

    // 图片框背景
    QPalette pal(ui->frame->palette());
    pal.setColor(QPalette::Background, QColor(255,255,255));
    ui->frame->setAutoFillBackground(true);
    ui->frame->setPalette(pal);

    ui->tableView_detect->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_detect->horizontalHeader()->hide();
    ui->tableView_detect->verticalHeader()->hide();
    ui->tableView_detect->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_detect->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // 数据库
    m_dbModel = new DBModel(this);

    ui->tableView_detect->setModel(m_dbModel->getdetectModel());

    m_messageHide = false;
}

void MessageOperate::initConnect()
{
    connect(ui->btn_message_status, SIGNAL(clicked()), this, SLOT(clickMessageStatusBtn()));

    // 消息框状态切换
    connect(ui->btn_msg_debug, &QPushButton::clicked, [&](){
            if ( m_messageHide ){
                clickMessageStatusBtn();
            }
            ui->stackedWidget->setCurrentWidget(ui->page_msg_debug);
            debugShowMessage("Message box debug page show.");
        });

    connect(ui->btn_msg_message, &QPushButton::clicked, [&](){
            if ( m_messageHide ){
                clickMessageStatusBtn();
            }
            ui->stackedWidget->setCurrentWidget(ui->page_msg_detect);
            debugShowMessage("Message box detect page show.");
        });
}

void MessageOperate::clickMessageStatusBtn()
{
    if ( !m_messageHide ){
        m_messageMaxHeight = this->maximumHeight();
        this->setMaximumHeight(ui->widget_button->size().height() + 5);
        ui->line->close();
        ui->widget_message->close();
        ui->btn_message_status->setIcon( Awesome::getInstace()->icon( fa::chevroncircleup, Awesome::getInstace()->options) );
        m_messageHide = true;
        debugShowMessage("Message box hide.");
    }
    else{
        this->setMaximumHeight(m_messageMaxHeight);
        ui->line->show();
        ui->widget_message->show();
        ui->btn_message_status->setIcon( Awesome::getInstace()->icon( fa::chevroncircledown, Awesome::getInstace()->options) );
        m_messageHide = false;
        debugShowMessage("Message box open.");
    }
}

void MessageOperate::debugShowMessage(QString message)
{
//    if (message.isEmpty())
//        return;
//    QDateTime _currentDateTime =QDateTime::currentDateTime();
//    QString _currentTime =_currentDateTime.toString("[ yyyy-MM-dd hh:mm:ss.zzz ]  ");
//    message = _currentTime + message;
//    m_debugListModel->insertRow(m_debugListModel->rowCount());
//    QModelIndex index = m_debugListModel->index(m_debugListModel->rowCount()-1,0);
//    m_debugListModel->setData(index, message, Qt::DisplayRole);
//    qDebug() << message;
}

void MessageOperate::detectShowMessage(QString message)
{

}

MessageOperate::~MessageOperate()
{
    delete ui;
}
