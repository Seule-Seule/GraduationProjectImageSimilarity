#ifndef DBMODEL_HPP
#define DBMODEL_HPP

#include "Tools/tool.hpp"

#include <QObject>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class DBModel : public QObject
{
    Q_OBJECT
public:
    explicit DBModel(QObject *parent = nullptr);

signals:
    void detectRefreshDisplay();
    void debugRefreshDisplay();

public:
    void insertDebugMessage(QString message);
    void insertDetectMessage(QString message);

private slots:
    void detectDisplay();
    void debugDisplay();

private:
    QSqlDatabase m_dataBase;
    QSqlQuery    *m_sqlQuery;
    PointerPropertyBuilderByName(QSqlQueryModel, detectModel, private);
    PointerPropertyBuilderByName(QSqlQueryModel, debugModel, private);
};

#endif // DBMODEL_HPP
