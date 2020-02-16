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
    QStringList list = path.split(" ");
    if (list.length()==0) return false;
    QString fullPath;
    if (list[0]=="sudo"){
        if (list.length()<2) return false;
        fullPath=list[1];
    } else {
        fullPath=list[0];
    }
    QFile file(fullPath);
    return file.exists();
}
