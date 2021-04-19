#ifndef DETECTDISPLAYMODEL_HPP
#define DETECTDISPLAYMODEL_HPP

#include "Model/basemodel.hpp"
#include "Tools/tool.hpp"
#include "View/imageshowview.hpp"

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

class DetectDisplayModel : public QObject
{
    Q_OBJECT
public:
    explicit DetectDisplayModel(QObject *parent = nullptr);

signals:
    void debugMessageSig(QString);
    void valueChange();

private slots:
    void updataDetectDisplay();
    void debugMessage(QString message);

public slots:
    void detectMessage(QString message);
    void setProjectId(QString id);

public:
    QSqlQueryModel   *qSqlQueryModel;

private:
    QSqlDatabase     *m_dataBase;
    QSqlQuery        *m_sqlQuery;
    QString           m_ProjectId;

    PointerPropertyBuilderByName(ImageInfo, LeftImageInfo, private);
    PointerPropertyBuilderByName(ImageInfo, RightImageInfo, private);
};

#endif // DETECTDISPLAYMODEL_HPP
