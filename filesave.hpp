#ifndef FILESAVE_H
#define FILESAVE_H
#define _CRT_SECURE_NO_WARNINGS

#include "tool.hpp"

#include <QObject>
#include <QFile>
#include <QPdfWriter>
#include <QStringListModel>
#include <QSqlQueryModel>

class FileSave : public QObject
{
    Q_OBJECT
public:
    explicit FileSave(QObject *parent = nullptr);

signals:

private:
    void initFileSave();
    void writeText(int fontSize, Qt::Alignment flags, QString message);
    void writeImage( const QPixmap &leftPixmap, const QPixmap &rightPixmap);

public:
    void save(const QSqlQueryModel &model, const QPixmap &leftPixmap, const QPixmap &rightPixmap);

signals:
    void sendStatusBarMessageSig(QString message, int timeout);
    void sendDebugMessageSig(QString message);
    void sendDetectMessageSig(QString message);

private:
    void debugShowMessage(QString message);
    void DetectShowMessage(QString message);
    void statusBurShowMessage(QString message, int timeout);

public:
    PropertyBuilderByName(QString, filePath, private);
    PropertyBuilderByName(QString, fileName, private);
    PropertyBuilderByName(bool, fileSave, private);
    PropertyBuilderByName(size_t, iTop, private);
    PropertyBuilderByName(size_t, iContentWidth, private);
    PointerPropertyBuilderByName(QPdfWriter, pPdfWriter, private);
    PointerPropertyBuilderByName(QPainter, pPdfPainter, private);

};

#endif // FILESAVE_H
