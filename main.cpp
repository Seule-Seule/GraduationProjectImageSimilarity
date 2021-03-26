#include "View/ImageSimilarityView.hpp"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageSimilarityView w;
    w.show();
    return a.exec();
}
