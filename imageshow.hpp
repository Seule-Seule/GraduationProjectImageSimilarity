#ifndef IMAGESHOW_HPP
#define IMAGESHOW_HPP

#include <QWidget>

namespace Ui {
class ImageShow;
}

class ImageShow : public QWidget
{
    Q_OBJECT

public:
    explicit ImageShow(QWidget *parent = nullptr);
    ~ImageShow();

private:
    Ui::ImageShow *ui;
};

#endif // IMAGESHOW_HPP
