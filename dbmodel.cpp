#include "dbmodel.hpp"

#include <QSqlError>
#include <QDateTime>

DBModel::DBModel(QObject *parent) : QObject(parent)
{
    m_dataBase = QSqlDatabase::addDatabase("QSQLITE");
    m_dataBase.setDatabaseName("imageSimilarity.db");
    m_dataBase.open();
    if( !m_dataBase.open() )
    {
        insertDebugMessage(QString("Database ") + m_dataBase.lastError().text());
        return;
    }
    else{
        insertDebugMessage(QString("Database open success !"));
    }

    m_sqlQuery = new QSqlQuery(m_dataBase);

    m_sqlQuery->exec("create table detect(algorithm,data,time,result)");
    m_sqlQuery->exec("create table debug(algorithm,data,time,message)");
    insertDebugMessage("Table create success !");

    m_detectModel = new QSqlQueryModel(this);

    //  在 数据更新时 更新信息框显示
    connect(m_detectModel, SIGNAL(detectRefreshDisplay()), this, SLOT(detectDisplay()));
    connect(m_debugModel, SIGNAL(debugRefreshDisplay()), this, SLOT(debugDisplay()));
}

void DBModel::detectDisplay()
{
    while(m_detectModel->canFetchMore())
    {
        m_detectModel->fetchMore();
    }
    m_detectModel->setQuery("select algorithm,result,time from detect");
}

void DBModel::debugDisplay()
{

}

void DBModel::insertDebugMessage(QString message)
{

}

void DBModel::insertDetectMessage(QString message)
{
    if (message.isEmpty()){
        insertDebugMessage("MessageOperate::detectShowMessage message is empty !");
        return;
    }

    QVector<QString> messageVector = Tool::splitQString(message, ":");
    if (messageVector.size() != 2){
        insertDebugMessage("MessageOperate::detectShowMessage splitQString error !");
        return;
    }

    QDateTime _currentDateTime =QDateTime::currentDateTime();
    QString _currentData =_currentDateTime.toString("yyyy-MM-dd");
    QString _currentTime =_currentDateTime.toString("hh:mm:ss.zzz");

    if (!m_sqlQuery->exec("insert into detect(algorithm,data,time,result) values('"+messageVector[0]+"','"+_currentData+"','"+_currentTime+"','"+messageVector[1]+"')")){
        insertDebugMessage(m_sqlQuery->lastError().text());
    }

    emit(detectRefreshDisplay());
}
