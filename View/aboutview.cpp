#include "aboutview.hpp"
#include "ui_aboutview.h"

AboutView::AboutView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutView)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("About Image Similarity Discrimination And Processing System"));

    QIcon qIcon = Awesome::getInstace()->icon( fa::image, Awesome::getInstace()->options);
    ui->label->setPixmap(qIcon.pixmap(ui->label->size(), QIcon::Normal));
}

AboutView::~AboutView()
{
    delete ui;
}
