#include "debugdisplaymodel.hpp"

#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QtConcurrent/QtConcurrent>

DebugDisplayModel::DebugDisplayModel(QObject *parent)
{
    m_dataBase = QSqlDatabase::addDatabase("QSQLITE");
    m_dataBase.setDatabaseName(Tool::getDatabaseName());
    m_dataBase.open();
    if( !m_dataBase.open() )
    {
        qDebug() << "DebugDisplayModel::Database " << m_dataBase.lastError().text();
        return;
    }

    m_sqlQuery = new QSqlQuery(m_dataBase);

    m_sqlQuery->exec(QString("create table debug(") + Tool::getDatabaseDebugTableKay() + QString(")"));

    qSqlQueryModel = new QSqlQueryModel(this);
    qSqlQueryModel-> setQuery( QString( "select ") + Tool::getDatabaseDebugTableShowKay() + QString(" from debug"));

    debugMessage("DebugDisplayModel::Database init ok !");
}

void DebugDisplayModel::updataDebugDisplay()
{
//    while(qSqlQueryModel->canFetchMore())
//    {
//        qSqlQueryModel->fetchMore();
//    }
    qSqlQueryModel-> setQuery( QString( "select ") + Tool::getDatabaseDebugTableShowKay() + QString(" from debug"));
    emit(valueChange());
}

void DebugDisplayModel::debugMessage(const QString message)
{
    if (message.isEmpty()){
        qDebug() << "DebugDisplayModel::debugMessage message is empty !";
        return;
    }

    QVector<QString> messageVector = Tool::splitQString(message, "::");
    if (messageVector.size() < 2 ){
        qDebug() << "DebugDisplayModel::debugMessage message have not class name ! ->" << message << "<-";
        return ;
    }
    QString className = messageVector[messageVector.size()-2];
    QString debugMessage = messageVector.back();

    QDateTime currentDateTime =QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");

    qDebug() << currentTime << className << debugMessage;

    if (!m_sqlQuery->exec("insert into debug(className,time,message) "
                          "values('"+className+"','"+currentTime+"','"+debugMessage+"')")){
        qDebug() << "DebugDisplayModel::debugMessage " << m_sqlQuery->lastError().text();
    }
    updataDebugDisplay();
}
