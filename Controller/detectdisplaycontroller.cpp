#include "detectdisplaycontroller.hpp"


DetectDisplayController::DetectDisplayController(MessageBoxView *messageBoxView,ImageInfo *LeftImageInfo,ImageInfo *RightImageInfo, QObject *parent)
{
    m_DetectDisplayModel = new DetectDisplayModel(this);
    m_DetectDisplayModel->setLeftImageInfo(LeftImageInfo);
    m_DetectDisplayModel->setRightImageInfo(RightImageInfo);

    messageBoxView->setDetectModel(m_DetectDisplayModel->qSqlQueryModel);

    connect(m_DetectDisplayModel, SIGNAL(valueChange()), messageBoxView, SLOT(update()));
    connect(messageBoxView, SIGNAL(detectMessageSig(QString)), m_DetectDisplayModel, SLOT(detectMessage(QString)));

    connect(messageBoxView, SIGNAL(projectIdSig(QString)), m_DetectDisplayModel, SLOT(setProjectId(QString)));
}
