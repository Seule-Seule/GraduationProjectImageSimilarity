#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "imageshow.hpp"
#include "awesome.hpp"
#include "value.hpp"
#include "messagebox.hpp"

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

    void debugShowMessage(QString message);
    void messageShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout);

private:
    void initUi();
    void initConnect();

private:
    Ui::MainWindow *ui;

public:
    PointerPropertyBuilderByName(ImageShow, leftImage, private);
    PointerPropertyBuilderByName(ImageShow, rightImage, private);
    PointerPropertyBuilderByName(MessageBox, messageBox, private);

};
#endif // MAINWINDOW_HPP
