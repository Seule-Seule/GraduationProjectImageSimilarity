#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "imageshow.hpp"
#include "awesome.hpp"
#include "value.hpp"
#include "messagebox.hpp"
#include "imagealgorithm.hpp"
#include "filesave.hpp"

#include <QMainWindow>
#include <QStringListModel>

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
    void clickSaveButton();
    void clickOpenButton();
    void clickOpHistogramButton();

private slots:
    void debugShowMessage(QString message);
    void detectShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout, bool selfUse = false /*是否调用，不是槽函数*/);

private:
    void initUi();
    void initConnect();
    Ui::MainWindow *ui;

public:
    PointerPropertyBuilderByName(ImageShow, leftImage, private);
    PointerPropertyBuilderByName(ImageShow, rightImage, private);
    PointerPropertyBuilderByName(MessageBox, messageBox, private);
    PointerPropertyBuilderByName(ImageAlgorithm, imageAlgorithm, private);
    PointerPropertyBuilderByName(FileSave, fileSave, private);
};

#endif // MAINWINDOW_HPP
