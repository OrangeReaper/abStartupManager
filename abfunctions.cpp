#include "abfunctions.h"

#include <QTime>
#include <QFile>
#include <QCoreApplication>

abFunctions::abFunctions()
{

}
void abFunctions::waitFor(int secs){

    QTime dieTime= QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
bool abFunctions::fileExists(QString path){
    QFile file(path);
    return file.exists();
}
