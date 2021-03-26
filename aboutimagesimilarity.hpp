#ifndef ABOUTIMAGESIMILARITY_HPP
#define ABOUTIMAGESIMILARITY_HPP

#include <QWidget>

namespace Ui {
class AboutImageSimilarity;
}

class AboutImageSimilarity : public QWidget
{
    Q_OBJECT

public:
    explicit AboutImageSimilarity(QWidget *parent = nullptr);
    ~AboutImageSimilarity();

private:
    Ui::AboutImageSimilarity *ui;
};

#endif // ABOUTIMAGESIMILARITY_HPP
