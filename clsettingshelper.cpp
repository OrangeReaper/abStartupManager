#include "clsettingshelper.h"

#include <QSettings>

clSettingsHelper::clSettingsHelper()
{

}
QStringList clSettingsHelper::getList(QString group){
    QStringList result;
    QSettings iSettings;

    iSettings.beginGroup(group);
    int size = iSettings.beginReadArray("names");

    for(int i=0;i<size;i++){
      iSettings.setArrayIndex(i);
      result.append(iSettings.value("name").toString());
    }
    iSettings.endArray();
    iSettings.endGroup();
    return result;
}

void clSettingsHelper::saveList(QString group, QStringList list){
    QSettings iSettings;
    iSettings.remove(group);
    iSettings.beginGroup(group);
    iSettings.beginWriteArray("names");
    for(int i=0; i<list.count();i++){
      iSettings.setArrayIndex(i);
      iSettings.setValue("name",list[i]);
    }
    iSettings.endArray();
    iSettings.endGroup();
}


