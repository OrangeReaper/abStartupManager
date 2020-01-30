#ifndef CLSETTINGS_H
#define CLSETTINGS_H

#include <QString>
#include <QDir>

class clSettings
{
public:
    clSettings();

    static void validate();
    static void reset();

    static QString configPath(){ return QDir::homePath() + "/.config/comicCat"; }
    static QString imagesPath(){ return configPath() + "/images";}

private:

};

#endif // CLSETTINGS_H
