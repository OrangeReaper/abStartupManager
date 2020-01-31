#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>
#include "generalsettingslayout.h"
#include "filelistlayout.h"

namespace Ui {
class dlgSettings;
}

class dlgSettings : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSettings(QWidget *parent = 0);
    ~dlgSettings();

public slots:
    void onAddProfile();
    void onRemoveProfile();

private:
    Ui::dlgSettings *ui;

    bool loadProfiles();
    bool saveProfileList();
    bool profileNameOK(QString name);

    void removeProfile(QString name);
    void removeProfileTabs();
    void removeProfileTab(int index);
    void removeProfileTab(QString name);

    void addProfileTab(QString name);
    void addProfile(QString name);



    generalSettingsLayout * m_generalSettingsLayout;
    fileListLayout * m_serverList;

    QString m_fileList;

    QStringList getProfiles();
    QStringList m_profile_list;
};

#endif // DLGSETTINGS_H
