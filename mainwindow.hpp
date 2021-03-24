#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "imageshow.hpp"
#include "awesome.hpp"
#include "tool.hpp"
#include "messageoperate.hpp"
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

private slots:
    void debugShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout, bool selfUse = false /*是否调用，不是槽函数*/);

    void on_action_about_triggered();
    void on_action_help_content_triggered();
    void on_action_file_exit_triggered();
    void on_action_file_save_triggered();

    void on_action_op_his_triggered();

private:
    void initUi();
    void initConnect();
    Ui::MainWindow *ui;

public:
    PointerPropertyBuilderByName(ImageShow, leftImage, private);
    PointerPropertyBuilderByName(ImageShow, rightImage, private);
    PointerPropertyBuilderByName(MessageOperate, messageOperate, private);
    PointerPropertyBuilderByName(ImageAlgorithm, imageAlgorithm, private);
    PointerPropertyBuilderByName(FileSave, fileSave, private);
};

#endif // MAINWINDOW_HPP
