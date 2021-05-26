#include "tool.hpp"

#include <QPalette>
#include <QDebug>

Tool::Tool()
{

}

QVector<QString> Tool::splitQString(const QString &str, const QString &pattern)
{
    char * strc = new char[strlen(str.toStdString().c_str())+1];
    strcpy(strc, str.toStdString().c_str());   //string转换成C-string
    QVector<QString> res;
    char* temp = strtok(strc, pattern.toStdString().c_str());
    while(temp != NULL)
    {
        res.push_back(QString(temp));
        temp = strtok(NULL, pattern.toStdString().c_str());
    }
    delete[] strc;
    return res;
}

void Tool::setUiElementColor(QWidget *wid, QColor color)
{
    // 设置背景
    QPalette pal1 = wid->palette();
    pal1.setColor(QPalette::Button, color);
    wid->setAutoFillBackground(true);
    wid->setPalette(pal1);
}

void Tool::setUiBackgroundColor(QWidget *wid, QColor color)
{
    // 设置背景
    QPalette pal1 = wid->palette();
    pal1.setColor(QPalette::Background, color);
    wid->setAutoFillBackground(true);
    wid->setPalette(pal1);
}

QString Tool::getDatabaseName()
{
    return QString("ImageSimilarity.db");
}

QString Tool::getDatabaseDebugTableKay()
{
    return QString("string_id,className,time,message");
}

QString Tool::getDatabaseDebugTableShowKay()
{
    return QString("time,className,message");
}

QString Tool::getDatabaseDetectTableKay()
{
    return QString("string_id,date,time,message,value,left_image_path,left_image_name,right_image_path,right_image_name");
}

QString Tool::getDatabaseDetectTableShowKay()
{
    return QString("time,message,value");
}



