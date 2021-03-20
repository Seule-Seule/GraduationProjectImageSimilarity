#ifndef FILESAVE_H
#define FILESAVE_H

#include "value.hpp"

#include <QObject>
#include <QFile>
#include <QPdfWriter>
#include <QStringListModel>

class FileSave : public QObject
{
    Q_OBJECT
public:
    explicit FileSave(QObject *parent = nullptr);

signals:

private:
    void initFileSave();

public:
    void save(const QStringListModel &model, const QPixmap &leftPixmap, const QPixmap &rightPixmap);

signals:
    void sendStatusBarMessageSig(QString message, int timeout);
    void sendDebugMessageSig(QString message);
    void sendDetectMessageSig(QString message);

private:
    void debugShowMessage(QString message);
    void DetectShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout);

public:
    enum fileType{
        PDF,
        CSV
    };

public:
    PropertyBuilderByName(fileType, fileType, private);
    PropertyBuilderByName(QString, filePath, private);
    PropertyBuilderByName(QString, fileName, private);
    PropertyBuilderByName(bool, fileSave, private);
    PropertyBuilderByName(size_t, sizeX, private);
    PropertyBuilderByName(size_t, sizeY, private);
    PointerPropertyBuilderByName(QPdfWriter, pPdfWriter, private);

};

#endif // FILESAVE_H
