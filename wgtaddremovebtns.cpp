#include "wgtaddremovebtns.h"
#include "ui_wgtaddremovebtns.h"

wgtAddRemoveBtns::wgtAddRemoveBtns(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgtAddRemoveBtns)
{
    ui->setupUi(this);
    m_removeButton = ui->btnRemove;
    m_addButton = ui->btnAdd;
}

wgtAddRemoveBtns::~wgtAddRemoveBtns()
{
    delete ui;
}
