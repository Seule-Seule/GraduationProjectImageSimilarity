#ifndef DEBUGDISPLAYCONTROLLER_HPP
#define DEBUGDISPLAYCONTROLLER_HPP

#include "basecontroller.hpp"
#include "View/messageboxview.hpp"
#include "Model/debugdisplaymodel.hpp"

#include <QObject>

class DebugDisPlayController : public QObject, public BaseController
{
    Q_OBJECT
public:
    explicit DebugDisPlayController(MessageBoxView *view, QObject *parent = nullptr);

signals:

private:
    DebugDisplayModel *m_debugDisplaymodel;

};

#endif // DEBUGDISPLAYCONTROLLER_HPP
