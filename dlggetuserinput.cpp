#include "dlggetuserinput.h"
#include "ui_dlggetuserinput.h"

dlgGetUserInput::dlgGetUserInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgGetUserInput)
{
    ui->setupUi(this);
    m_text=ui->lineEdit;
}

dlgGetUserInput::~dlgGetUserInput()
{
    delete ui;
}
