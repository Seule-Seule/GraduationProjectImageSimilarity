#ifndef MESSAGEBOXVIEW_HPP
#define MESSAGEBOXVIEW_HPP

#include "View/baseview.hpp"
#include "Tools/awesome.hpp"

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class MessageBoxView;
}

class MessageBoxView : public QWidget, public BaseView
{
    Q_OBJECT

public:
    explicit MessageBoxView(QWidget *parent = nullptr);
    ~MessageBoxView();

    void setDebugModel(QAbstractItemModel *model);

signals:
    void debugMessageSig(QString);

public slots:
    virtual void update();
    void debugMessage(QString message);

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
