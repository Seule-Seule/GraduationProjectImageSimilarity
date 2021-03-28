#include "debugdisplaycontroller.hpp"

DebugDisPlayController::DebugDisPlayController(MessageBoxView *view, QObject *parent) : QObject(parent)
{
    m_debugDisplaymodel = new DebugDisplayModel(this);
    view->setDebugModel(m_debugDisplaymodel->qSqlQueryModel);
    connect(m_debugDisplaymodel, SIGNAL(valueChange()), view, SLOT(update()));
    connect(view, SIGNAL(debugMessageSig(QString)), m_debugDisplaymodel, SLOT(debugMessage(QString)));

    connect(view, SIGNAL(projectIdSig(QString)), m_debugDisplaymodel, SLOT(setProjectId(QString)));
}

