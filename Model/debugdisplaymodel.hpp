#ifndef DEBUGDISPLAYMODEL_H
#define DEBUGDISPLAYMODEL_H

#include "Tools/tool.hpp"
#include "Model/basemodel.hpp"

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

class DebugDisplayModel : public QObject, public BaseModel
{
    Q_OBJECT

public:
    DebugDisplayModel(QObject *parent = nullptr);

signals:
    void valueChange();

public slots:
    virtual void debugMessage(const QString message);

private slots:
    void updataDebugDisplay();

public:
    QSqlQueryModel   *qSqlQueryModel;

private:
    QSqlDatabase     m_dataBase;
    QSqlQuery        *m_sqlQuery;
};

#endif // DEBUGDISPLAYMODEL_H
