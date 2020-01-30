#include "abfunctions.h"

#include <QTime>
#include <QCoreApplication>

abFunctions::abFunctions()
{

}
void abFunctions::waitFor(int secs){

    QTime dieTime= QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
