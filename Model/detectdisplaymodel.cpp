#include "detectdisplaymodel.hpp"

#include <QSqlError>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QtConcurrent>

DetectDisplayModel::DetectDisplayModel(QObject *parent) : QObject(parent)
{
    m_dataBase = BaseModel::getDatabase();
    m_sqlQuery = BaseModel::getQSqlQuery();
    m_ProjectId = QString::number(0);

    m_sqlQuery->exec(QString("create table detect(") + Tool::getDatabaseDetectTableKay() + QString(")"));

    qSqlQueryModel = new QSqlQueryModel(this);
    qSqlQueryModel->setQuery( QString( "select ") + Tool::getDatabaseDetectTableShowKay() + \
            QString(" from detect where string_id = '"+m_ProjectId+"'"),*BaseModel::getDatabase());

}

void DetectDisplayModel::debugMessage(QString message)
{
    QString objName = this->objectName();
    message = objName + QString("::") + message;
    emit(debugMessageSig(message));
}

void DetectDisplayModel::updataDetectDisplay()
{
    QtConcurrent::run([=](){
        qSqlQueryModel->setQuery( QString( "select ") + Tool::getDatabaseDetectTableShowKay() + \
        QString(" from detect where string_id = '"+m_ProjectId+"'"),*BaseModel::getDatabase());
    });
    emit(valueChange());
}

void DetectDisplayModel::setProjectId(QString id)
{
    m_ProjectId = id;
}

void DetectDisplayModel::detectMessage(QString message)
{
    if (message.isEmpty()){
        debugMessage("detectMessage message is empty !");
        return;
    }

    if (m_ProjectId == 0){
        debugMessage("Project id is 0 !");
        return;
    }

    QVector<QString> messageVector = Tool::splitQString(message, "::");
    if (messageVector.size() < 2 ){
        debugMessage("detectMessage message have not class name ! ");
        return ;
    }
    QString detectMessage = messageVector[messageVector.size()-2];
    QString detectValue = messageVector.back();

    QDateTime currentDateTime =QDateTime::currentDateTime();
    QString currentDate = currentDateTime.toString("yyyy-MM-dd");
    QString currentTime = currentDateTime.toString("hh:mm:ss.zzz");
    QString left_image_path = m_LeftImageInfo->getImagePath();
    QString left_image_name = m_LeftImageInfo->getImageName();
    QString right_image_path = m_RightImageInfo->getImagePath();
    QString right_image_name = m_RightImageInfo->getImageName();

//    "id string_id,
//    date,time,message,value,
//    left_image_path,left_image_name,left_image_po,
//    right_image_path,right_image_name,right_image_po

    if (!m_sqlQuery->exec("insert into detect(                                   \
                           string_id,date,time,message,value,                    \
                           left_image_path,left_image_name,       \
                           right_image_path,right_image_name)     \
     values('"+m_ProjectId+"','"+currentDate+"','"+currentTime+"','"+detectMessage+"','"+detectValue+"',\
                                 '"+left_image_path+"','"+left_image_name+"',             \
                                 '"+right_image_path+"','"+right_image_name+"')")){
        debugMessage(QString("debugMessage") + m_sqlQuery->lastError().text());
    }
    updataDetectDisplay();
}
