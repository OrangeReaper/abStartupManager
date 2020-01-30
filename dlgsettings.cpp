#include "dlgsettings.h"
#include "ui_dlgsettings.h"

dlgSettings::dlgSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSettings)
{
    ui->setupUi(this);
    m_generalSettingsLayout = new generalSettingsLayout();
    ui->tabGeneral->setLayout(m_generalSettingsLayout);

    m_serverList = new fileListLayout(0, "Servers", "ovpn Files (*.ovpn)" );
    ui->tabServers->setLayout(m_serverList);
}

dlgSettings::~dlgSettings()
{
    delete ui;
    m_generalSettingsLayout->deleteLater();
}


