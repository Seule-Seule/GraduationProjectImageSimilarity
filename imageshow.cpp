#include "imageshow.hpp"
#include "ui_imageshow.h"


#include "QtAwesome.h"

ImageShow::ImageShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageShow)
{
    ui->setupUi(this);

    QtAwesome* awesome = new QtAwesome(this);
    awesome->initFontAwesome();

    // icon
    ui->button_history_im->setFlat(true);
    ui->button_open_im->setFlat(true);
    ui->button_load_im->setFlat(true);
    ui->button_open_im->setIcon( awesome->icon( fa::folderopen) );
    ui->button_load_im->setIcon( awesome->icon( fa::spinner) );
    ui->button_history_im->setIcon(awesome->icon( fa::chevrondown));
    ui->label_path_im->setText(QString(""));
}

ImageShow::~ImageShow()
{
    delete ui;
}
