#include "messageboxview.hpp"
#include "ui_messageboxview.h"

#include <QTimer>

MessageBoxView::MessageBoxView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageBoxView)
{
    ui->setupUi(this);

    initUi();
}

MessageBoxView::~MessageBoxView()
{
    delete ui;
}

void MessageBoxView::initUi()
{
    // 消息框
    ui->btn_message_status->setIcon( Awesome::getInstace()->icon( fa::chevroncircledown, Awesome::getInstace()->options) );
    ui->btn_message_status->setFlat(true);
    ui->btn_message_status->setStatusTip(tr("Show or close the message box!"));
    ui->btn_msg_debug->setFlat(true);
    ui->btn_msg_debug->setStatusTip(tr("Show debug message in message box!"));
    ui->btn_msg_message->setFlat(true);
    ui->btn_msg_message->setStatusTip(tr("Show image similarity message in message box!"));

    // 背景
    Tool::setUiBackgroundColor(this, Awesome::getInstace()->getUiBackgroundColor());

    ui->tableView_detect->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_detect->horizontalHeader()->hide();
    ui->tableView_detect->verticalHeader()->hide();
    ui->tableView_detect->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_detect->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_detect->setShowGrid(false);

    ui->tableView_debug->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_debug->horizontalHeader()->hide();
    ui->tableView_debug->verticalHeader()->hide();
    ui->tableView_debug->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_debug->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_debug->setShowGrid(false);


    ui->stackedWidget->setCurrentWidget(ui->page_msg_detect);
    ui->btn_msg_message->setFlat(true);
    ui->btn_msg_debug->setFlat(true);

    // 设置message按钮背景
    Tool::setUiElementColor(ui->btn_msg_message, Awesome::getInstace()->getUiEmementColor());

    m_messageHide = false;
}

void MessageBoxView::update()
{
    ui->tableView_debug->scrollToBottom();
    ui->tableView_detect->scrollToBottom();
}

void MessageBoxView::debugMessage(QString message)
{
    QString objName = this->objectName();
    message = objName + QString("::") + message;
    emit(debugMessageSig(message));
}

void MessageBoxView::detectMessage(QString message)
{
    emit(detectMessageSig(message));
}

void MessageBoxView::setDebugModel(QAbstractItemModel *model)
{
    ui->tableView_debug->setModel(model);
}

void MessageBoxView::setDetectModel(QAbstractItemModel *model)
{
    ui->tableView_detect->setModel(model);
}

void MessageBoxView::on_btn_message_status_clicked()
{
    if ( !m_messageHide ){
        m_widgetMessageSize = this->size();
        this->setMaximumSize(QSize(ui->widget_button->size().width(), ui->widget_button->size().height()+3 ));
        ui->widget_message->close();
        ui->line->close();
        ui->btn_message_status->setIcon( Awesome::getInstace()->icon( fa::chevroncircleup, Awesome::getInstace()->options) );
        m_messageHide = true;
        debugMessage("Message box hide.");
    }
    else{
        this->setMaximumSize(m_widgetMessageSize);
        ui->widget_message->show();
        ui->line->show();
        ui->btn_message_status->setIcon( Awesome::getInstace()->icon( fa::chevroncircledown, Awesome::getInstace()->options) );
        m_messageHide = false;
        debugMessage("Message box open.");
    }
}

void MessageBoxView::on_btn_msg_debug_clicked()
{
    if ( m_messageHide ){
        on_btn_message_status_clicked();
    }
    ui->stackedWidget->setCurrentWidget(ui->page_msg_debug);
    Tool::setUiElementColor(ui->btn_msg_debug, Awesome::getInstace()->getUiEmementColor());
    Tool::setUiElementColor(ui->btn_msg_message, Awesome::getInstace()->getUiBackgroundColor());

    debugMessage("Message box debug page show.");
}

void MessageBoxView::on_btn_msg_message_clicked()
{
    if ( m_messageHide ){
        on_btn_message_status_clicked();
    }
    ui->stackedWidget->setCurrentWidget(ui->page_msg_detect);
    Tool::setUiElementColor(ui->btn_msg_message, Awesome::getInstace()->getUiEmementColor());
    Tool::setUiElementColor(ui->btn_msg_debug, Awesome::getInstace()->getUiBackgroundColor());

    debugMessage("Message box detect page show.");
}
