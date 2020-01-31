#include "dlgselectfromlist.h"
#include "ui_dlgselectfromlist.h"

dlgSelectFromList::dlgSelectFromList(QWidget *parent, QStringList list) :
    QDialog(parent),
    ui(new Ui::dlgSelectFromList)
{
    ui->setupUi(this);
    ui->comboBox->addItems(list);
    m_combobox=ui->comboBox;
}

dlgSelectFromList::~dlgSelectFromList()
{
    delete ui;
}
