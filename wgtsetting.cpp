#include "wgtsetting.h"
#include "ui_wgtsetting.h"

#include <QSettings>

wgtSetting::wgtSetting(QWidget *parent, QString setting, QString value) :
    QWidget(parent),
    ui(new Ui::wgtSetting)
{
    ui->setupUi(this);

    ui->value->setStyleSheet("QWidget:disabled{color: #64B2D1;}"
                             "QWidget{color: blue;}");

    m_setting=setting;
    m_value=value;

    showSetting();

    setMode(false);
}

wgtSetting::~wgtSetting()
{
    delete ui;
}
void wgtSetting::setMode(bool editing){
    m_editing=editing;
    ui->value->setEnabled(editing);
    ui->cancel->setEnabled(editing);
    if (editing){
        ui->action->setIcon(QIcon(":/images/GreenTick.png"));
    } else {
         ui->action->setIcon(QIcon(":/images/Edit.png"));
    }
}
void wgtSetting::onAction(){
    if (m_editing) updateValue();
    setMode(!m_editing);
}
void wgtSetting::onCancel(){
    showSetting();
    setMode(!m_editing);
}
void wgtSetting::updateValue(){
    QSettings settings;
    m_value=ui->value->text();
    settings.setValue(m_setting, m_value);
}
void wgtSetting::showSetting(){
    ui->value->setText(m_value);
    ui->label->setText(m_setting);
}
