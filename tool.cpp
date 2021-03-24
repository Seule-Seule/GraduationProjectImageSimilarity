#include "tool.hpp"

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

