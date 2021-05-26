#include "basemodel.hpp"

#include "Tools/tool.hpp"

#include <QSqlError>
#include <QtDebug>

#include <io.h>
#include <direct.h>
#include <fstream>

QSqlDatabase *BaseModel::m_dataBase = nullptr;
QSqlQuery *BaseModel::m_sqlQuery = nullptr;
bool BaseModel::bFirstInit = false;

BaseModel::BaseModel()
{
    m_sqlQuery = nullptr;
    m_dataBase = nullptr;

    if(!bFirstInit)
    {
        if (_access(Tool::getDatabaseName().toStdString().c_str(), 0) == 0)
        {
            remove(Tool::getDatabaseName().toStdString().c_str());
        }
        bFirstInit = true;
    }
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
