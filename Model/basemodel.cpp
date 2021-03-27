#include "basemodel.hpp"

#include "Tools/tool.hpp"

#include <QSqlError>
#include <QtDebug>

QSqlDatabase *BaseModel::m_dataBase = nullptr;
QSqlQuery *BaseModel::m_sqlQuery = nullptr;

BaseModel::BaseModel()
{
    m_sqlQuery = nullptr;
}

QSqlDatabase *BaseModel::getDatabase()
{
    if (m_dataBase == nullptr){
        m_dataBase= new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        m_dataBase->setDatabaseName(Tool::getDatabaseName());
        m_dataBase->open();
        if( !m_dataBase->open()){
            qDebug() << "DebugDisplayModel::Database " << m_dataBase->lastError().text();
            return nullptr;
        }
        m_sqlQuery = new QSqlQuery(*m_dataBase);
    }
    return m_dataBase;
}

QSqlQuery *BaseModel::getQSqlQuery()
{
    if (m_sqlQuery == nullptr){
        qDebug() << "m_sqlQuery == nullptr";
        return nullptr;
    }
    return m_sqlQuery;
}
