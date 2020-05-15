#include "wgtaddremovebtns.h"
#include "ui_wgtaddremovebtns.h"

wgtAddRemoveBtns::wgtAddRemoveBtns(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgtAddRemoveBtns)
{
    ui->setupUi(this);
    m_removeButton = ui->btnRemove;
    m_addButton = ui->btnAdd;
    m_blacklistButton = ui->btnBlacklist;
    setBlacklistButton();
}

wgtAddRemoveBtns::~wgtAddRemoveBtns()
{
    delete ui;
}
void wgtAddRemoveBtns::setBlacklistBtn(bool blacklist){
    m_blacklist=blacklist;
    setBlacklistButton();
}
void wgtAddRemoveBtns::setBlacklistButton(){
    if (m_blacklist){
        ui->btnBlacklist->setIcon(QIcon(":/images/blacklist_icon.png"));
        ui->btnBlacklist->setToolTip("Blacklist Selected");
    } else {
        ui->btnBlacklist->setIcon(QIcon(":/images/whitelist_icon.png"));
        ui->btnBlacklist->setToolTip("Whitelist Selected");
    }
}
void wgtAddRemoveBtns::onBlacklistButton(){
    emit blacklistServers(m_blacklist);
}
