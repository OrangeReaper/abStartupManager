#include "generalsettingslayout.h"
#include <QSettings>
#include "wgtsetting.h"

generalSettingsLayout::generalSettingsLayout(QWidget *parent): QVBoxLayout(parent)
{
    QSettings settings;
    for(QString &key : settings.allKeys()){
        QString value = settings.value(key).toString();

        if (!ignore(key)){
            wgtSetting * setting = new wgtSetting(this->widget(), key, value);
            addWidget(setting);
        }
    }
}
generalSettingsLayout::~generalSettingsLayout(){
}
bool generalSettingsLayout::ignore(QString setting){
    if (setting.contains("/names/")) return true;
    QStringList ignoreSettings;
    ignoreSettings << "windowState" << "geometry";
    return ignoreSettings.contains(setting);

}

