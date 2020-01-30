#ifndef CLSETTINGSHELPER_H
#define CLSETTINGSHELPER_H

#include <QString>
#include <QStringList>

class clSettingsHelper
{
public:
    clSettingsHelper();

    static QStringList getList(QString group);
    static void saveList(QString group, QStringList list);

private:

};

#endif // CLSETTINGSHELPER_H
