#ifndef MESSAGEBOXVIEW_HPP
#define MESSAGEBOXVIEW_HPP

#include "Tools/awesome.hpp"

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class MessageBoxView;
}

class MessageBoxView : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBoxView(QWidget *parent = nullptr);
    ~MessageBoxView();

    void setDebugModel(QAbstractItemModel *model);
    void setDetectModel(QAbstractItemModel *model);

signals:
    void debugMessageSig(QString);
    void detectMessageSig(QString);

public slots:
    void update();
    void debugMessage(QString message);
    void detectMessage(QString message);

private slots:
    void initUi();
    void on_btn_message_status_clicked();
    void on_btn_msg_debug_clicked();
    void on_btn_msg_message_clicked();

private:
    Ui::MessageBoxView *ui;
    bool m_messageHide;
    QSize  m_widgetMessageSize;
};

#endif // MESSAGEBOXVIEW_HPP
