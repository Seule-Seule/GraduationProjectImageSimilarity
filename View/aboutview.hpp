#ifndef ABOUTVIEW_HPP
#define ABOUTVIEW_HPP

#include <QWidget>

#include "Tools/awesome.hpp"

namespace Ui {
class AboutView;
}

class AboutView : public QWidget
{
    Q_OBJECT

public:
    explicit AboutView(QWidget *parent = nullptr);
    ~AboutView();

private:
    Ui::AboutView *ui;
};

#endif // ABOUTVIEW_HPP
