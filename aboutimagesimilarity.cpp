#include "aboutimagesimilarity.hpp"
#include "ui_aboutimagesimilarity.h"

#include "tools/awesome.hpp"

#include <QPixmap>

AboutImageSimilarity::AboutImageSimilarity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutImageSimilarity)
{
    ui->setupUi(this);
    this->setWindowTitle("About Image Similarity Discrimination And Processing System");

    QIcon qIcon = Awesome::getInstace()->icon( fa::image, Awesome::getInstace()->options);
    ui->label->setPixmap(qIcon.pixmap(ui->label->size(), QIcon::Normal));

}

AboutImageSimilarity::~AboutImageSimilarity()
{
    delete ui;
}
