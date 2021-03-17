#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "imageshow.hpp"

#include <QMainWindow>

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

    void statusBurShowMessage(QString message, int timeout);

private:
    Ui::MainWindow *ui;

    PointerPropertyBuilderByName(ImageShow, leftImage, private);
    PointerPropertyBuilderByName(ImageShow, rightImage, private);
};
#endif // MAINWINDOW_HPP
