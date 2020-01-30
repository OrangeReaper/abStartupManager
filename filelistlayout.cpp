#include "filelistlayout.h"


fileListLayout::fileListLayout(QWidget *parent, QString fileListName, QString nameFilter): QVBoxLayout(parent)
{
    m_fileList = new fileList(this->widget(), fileListName, nameFilter);
    addWidget(m_fileList);
    connect(m_fileList, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    m_addRemoveBtns = new wgtAddRemoveBtns(this->widget());
    addWidget(m_addRemoveBtns);
    connect(m_addRemoveBtns->addButton(), SIGNAL(pressed()), m_fileList, SLOT(addFiles()));
    connect(m_addRemoveBtns->removeButton(), SIGNAL(pressed()), m_fileList, SLOT(removeSelected()));

    selectionChanged();

}
fileListLayout::~fileListLayout(){
    delete m_fileList;
    delete m_addRemoveBtns;
}

void fileListLayout::selectionChanged(){
    m_addRemoveBtns->removeButton()->setEnabled(m_fileList->selectedItems().count() > 0);
}
