#include "debugdisplaymodel.hpp"

#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QtConcurrent>

#define DEBUG

DebugDisplayModel::DebugDisplayModel(QObject *parent)
{
    m_dataBase = BaseModel::getDatabase();
    m_sqlQuery = BaseModel::getQSqlQuery();
    m_sqlQuery->exec(QString("create table debug(") + Tool::getDatabaseDebugTableKay() + QString(")"));

    qSqlQueryModel = new QSqlQueryModel(this);

    // 避免 启动时 debug 数据过大 卡死界面
    QtConcurrent::run([=](){
        qSqlQueryModel-> setQuery( QString( "select ") + Tool::getDatabaseDebugTableShowKay() + QString(" from debug"),*BaseModel::getDatabase());
    });
}

void DebugDisplayModel::updataDebugDisplay()
{
        qSqlQueryModel-> setQuery( QString( "select ") + Tool::getDatabaseDebugTableShowKay() + QString(" from debug"),*BaseModel::getDatabase());
    emit(valueChange());
}

void DebugDisplayModel::setProjectId(QString id)
{
    m_projectId = id;
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

    QString projectId = m_projectId;

    if (!m_sqlQuery->exec("insert into debug(string_id,className,time,message) "
                          "values('"+projectId+"','"+className+"','"+currentTime+"','"+debugMessage+"')")){
        #ifdef DEBUG
                qDebug() << "DebugDisplayModel::debugMessage " << m_sqlQuery->lastError().text();
        #endif
    }
    #ifdef DEBUG
        qDebug() << currentTime << className << debugMessage;
    #endif
    updataDebugDisplay();
}
