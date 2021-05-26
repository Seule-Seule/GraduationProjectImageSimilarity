#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class BaseModel
{
public:
    BaseModel();
    static QSqlDatabase *getDatabase();
    static QSqlQuery *getQSqlQuery();
private:
    bool initFlag;
    static QSqlDatabase *m_dataBase;
    static QSqlQuery        *m_sqlQuery;
    static bool bFirstInit;
};

#endif // BASEMODEL_HPP
