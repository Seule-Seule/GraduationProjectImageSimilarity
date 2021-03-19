#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <QWidget>
#include <QStringListModel>

namespace Ui {
class MessageBox;
}

class MessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr);
    ~MessageBox();

private:
    void initUi();
    void initConnect();

public slots:
    void clickMessageStatusBtn();

    void debugShowMessage(QString message);
    void messageShowMessage(QString message);

signals:
    void sendStatusBarMessageSig(QString, int);

private:
    Ui::MessageBox *ui;
    bool m_messageHide;
    int  m_messageMaxHeight;
    QStringListModel *m_debugListModel;
    QStringListModel *m_messageListModel;
};

#endif // MESSAGEBOX_HPP
