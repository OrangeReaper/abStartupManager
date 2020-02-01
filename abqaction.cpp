#include "abqaction.h"

abQAction::abQAction(QString text, QObject *parent) : QAction(text, parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(emitTriggered()));
}
void abQAction::emitTriggered(){
    emit triggered(text());
}
