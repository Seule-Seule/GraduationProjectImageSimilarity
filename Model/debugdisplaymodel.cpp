#include "debugdisplaymodel.hpp"

#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QtConcurrent/QtConcurrent>

DebugDisplayModel::DebugDisplayModel(QObject *parent)
{
    m_dataBase = BaseModel::getDatabase();
    m_sqlQuery = BaseModel::getQSqlQuery();
    m_sqlQuery->exec(QString("create table debug(") + Tool::getDatabaseDebugTableKay() + QString(")"));

    qSqlQueryModel = new QSqlQueryModel(this);
    qSqlQueryModel-> setQuery( QString( "select ") + Tool::getDatabaseDebugTableShowKay() + QString(" from debug"),*BaseModel::getDatabase());

    debugMessage("DebugDisplayModel::Database init ok !");
}

void DebugDisplayModel::updataDebugDisplay()
{
//    while(qSqlQueryModel->canFetchMore())
//    {
//        qSqlQueryModel->fetchMore();
//    }
    qSqlQueryModel-> setQuery( QString( "select ") + Tool::getDatabaseDebugTableShowKay() + QString(" from debug"),*BaseModel::getDatabase());
    emit(valueChange());
}

void DebugDisplayModel::debugMessage(const QString message)
{
    if (message.isEmpty()){
        #ifdef DEBUG
            qDebug() << "DebugDisplayModel::debugMessage message is empty !";
        #endif
        return;
    }

    QVector<QString> messageVector = Tool::splitQString(message, "::");
    if (messageVector.size() < 2 ){
        #ifdef DEBUG
            qDebug() << "DebugDisplayModel::debugMessage message have not class name ! ->" << message << "<-";
        #endif
        return ;
    }
    QString className = messageVector[messageVector.size()-2];
    QString debugMessage = messageVector.back();

    QDateTime currentDateTime =QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");



    if (!m_sqlQuery->exec("insert into debug(className,time,message) "
                          "values('"+className+"','"+currentTime+"','"+debugMessage+"')")){
        #ifdef DEBUG
                qDebug() << "DebugDisplayModel::debugMessage " << m_sqlQuery->lastError().text();
        #endif
    }
    #ifdef DEBUG
        qDebug() << currentTime << className << debugMessage;
    #endif
    updataDebugDisplay();
}
