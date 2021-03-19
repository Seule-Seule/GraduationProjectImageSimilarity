#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "imageshow.hpp"
#include "QtAwesome.h"

#include <QMainWindow>
#include <qstringlistmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void clickExitButton();
    void clickOpenButton();
    void clickMessageStatusBtn();

    void debugShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout);

private:
    void initUi();
    void initModel();
    void initConnect();

private:
    Ui::MainWindow *ui;

public:
    PointerPropertyBuilderByName(ImageShow, leftImage, private);
    PointerPropertyBuilderByName(ImageShow, rightImage, private);

private:
    bool  messageHide;
    QtAwesome *m_iconAwesome;
    QVariantMap m_iocnOptions;
    QStringListModel *m_debugListModel;
};
#endif // MAINWINDOW_HPP
