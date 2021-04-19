#ifndef DETECTDISPLAYCONTROLLER_HPP
#define DETECTDISPLAYCONTROLLER_HPP

#include "View/messageboxview.hpp"
#include "View/imageshowview.hpp"

#include "Model/detectdisplaymodel.hpp"

#include <QObject>

class DetectDisplayController : public QObject
{
    Q_OBJECT
public:
    explicit DetectDisplayController(MessageBoxView *messageBoxView,ImageInfo *LeftImageInfo,ImageInfo *RightImageInfo, QObject *parent = nullptr);

signals:
    void valueChange();

private:
    DetectDisplayModel *m_DetectDisplayModel;
};

#endif // DETECTDISPLAYCONTROLLER_HPP
