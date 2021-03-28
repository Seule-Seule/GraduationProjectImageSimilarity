#ifndef DEBUGDISPLAYMODEL_H
#define DEBUGDISPLAYMODEL_H

#include "Tools/tool.hpp"
#include "Model/basemodel.hpp"

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class DebugDisplayModel : public QObject
{
    Q_OBJECT

public:
    DebugDisplayModel(QObject *parent = nullptr);

signals:
    void valueChange();

public slots:
    void debugMessage(const QString message);
    void setProjectId(QString id);

private slots:
    void updataDebugDisplay();

public:
    QSqlQueryModel   *qSqlQueryModel;

private:
    QSqlDatabase     *m_dataBase;
    QSqlQuery        *m_sqlQuery;
    PropertyBuilderByName(QString, projectId, private);
};

#endif // DEBUGDISPLAYMODEL_H
