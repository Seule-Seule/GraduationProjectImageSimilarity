#include "View/ImageSimilarityView.hpp"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageSimilarityView w;
    qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);
    w.show();
    return a.exec();
}
