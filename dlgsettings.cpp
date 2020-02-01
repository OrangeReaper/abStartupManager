#include "dlgsettings.h"
#include "ui_dlgsettings.h"
#include "clsettingshelper.h"
#include "dlgselectfromlist.h"
#include "dlggetuserinput.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QStringList>
#include <QSettings>

dlgSettings::dlgSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSettings)
{
    ui->setupUi(this);
    m_generalSettingsLayout = new generalSettingsLayout();
    ui->tabGeneral->setLayout(m_generalSettingsLayout);

    m_serverList = new fileListLayout(0, MainWindow::defaultProfile(), "ovpn Files (*.ovpn)" );
    ui->tabServers->setLayout(m_serverList);

    ui->actionRemoveProfile->setEnabled(loadProfiles());
}

dlgSettings::~dlgSettings()
{
    delete ui;
    m_generalSettingsLayout->deleteLater();
}


void dlgSettings::onAddProfile(){
    dlgGetUserInput dialog(this);
    if ((dialog.exec() == QDialog::Accepted) && profileNameOK(dialog.text())){
        addProfile(dialog.text());
    } else {
        return;
    }

    ui->tabWidget->setCurrentIndex(1);
    //ui->actionRemoveProfile->setEnabled(ui->tabWidget->count()<3);
}
bool dlgSettings::profileNameOK(QString name){
    QString result="OK";
    QStringList notAllowed;
    notAllowed << MainWindow::defaultProfile() << "General";
    if (m_profile_list.contains(name)) result = "Profile Name Already Exists" ;
    if (notAllowed.contains(name)) result = "Profile Name is Not Allowed (Reserved)";
    if (result == "OK"){
        return true;
    }
    QMessageBox msgBox;
    msgBox.setText("Profile Name is not Acceptable.");
    msgBox.setDetailedText(result);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
    return false;
}
void dlgSettings::onRemoveProfile(){

    dlgSelectFromList dialog(this, getProfiles());
    if (dialog.exec() == QDialog::Accepted){
        removeProfile(dialog.selectedItem());
    } else {
        return;
    }

    ui->tabWidget->setCurrentIndex(1);
    //ui->actionRemoveProfile->setEnabled(ui->tabWidget->count()<3);
}
void dlgSettings::removeProfile(QString name){
    removeProfileTab(name);
    m_profile_list.removeOne(name);
    QSettings settings;
    settings.remove(name);
    saveProfileList();
}
void dlgSettings::addProfile(QString name){
    addProfileTab(name);
    m_profile_list.append(name);
    saveProfileList();
}
bool dlgSettings::loadProfiles(){
    //Return FALSE if there are no profiles to load
    removeProfileTabs();

    m_profile_list=getProfiles();
    if (m_profile_list.length() == 0) return false;

    for (QString profile : m_profile_list){
        addProfileTab(profile);
    }
    return true;
}
bool dlgSettings::saveProfileList(){
    clSettingsHelper m_settingsHelper;
    m_settingsHelper.saveList("Profiles", m_profile_list);
    bool result = m_profile_list.size() > 0;
    ui->actionRemoveProfile->setEnabled(result);
    emit profilesChanged();
    return result;
}
QStringList dlgSettings::getProfiles(){
    clSettingsHelper m_settingsHelper;
    return m_settingsHelper.getList("Profiles");
}
void dlgSettings::removeProfileTabs(){
    //Delete tabs with index > 1
    while (ui->tabWidget->count() > 2){
        removeProfileTab(2);
    }
}
void dlgSettings::addProfileTab(QString name){

    QWidget *newTab = new QWidget( ui->tabWidget);
    ui->tabWidget->addTab(newTab, name);

    fileListLayout * list;
    list = new fileListLayout(0, name, "ovpn Files (*.ovpn)" );
    newTab->setLayout(list);

}
void dlgSettings::removeProfileTab(int index){
    QWidget *widget;
    widget = ui->tabWidget->widget(index); // remember widget
    ui->tabWidget->removeTab(index); // remove tab
    widget->deleteLater(); // remove widget
}
void dlgSettings::removeProfileTab(QString name){
    for ( int i=ui->tabWidget->count()-1; i>=0; --i) {
        if (ui->tabWidget->tabText(i) == name){
            removeProfileTab(i); // remove tab
            break;
        }
    }
}
