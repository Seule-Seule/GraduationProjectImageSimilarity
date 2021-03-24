#ifndef MESSAGEOPERATE_H
#define MESSAGEOPERATE_H

#include "dbmodel.hpp"

#include <QWidget>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class MessageOperate;
}

class MessageOperate : public QWidget
{
    Q_OBJECT

public:
    explicit MessageOperate(QWidget *parent = nullptr);
    ~MessageOperate();

private:
    void initUi();
    void initConnect();
    void initDataBase();

public slots:
    void clickMessageStatusBtn();

    void debugShowMessage(QString message);
    void detectShowMessage(QString message);

signals:
    void sendStatusBarMessageSig(QString, int);

private:
    Ui::MessageOperate *ui;
    bool m_messageHide;
    int  m_messageMaxHeight;
    DBModel *m_dbModel;

};

#endif // MESSAGEOPERATE_H
