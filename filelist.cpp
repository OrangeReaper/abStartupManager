#include "filelist.h"
#include <QFileDialog>

fileList::fileList(QWidget *parent, QString fileList, QString nameFilter): QListWidget(parent){
    m_fileList=fileList;
    m_nameFilter=nameFilter;
    m_settingsHelper = new clSettingsHelper();
    m_list=m_settingsHelper->getList(fileList);
    addItems(m_list);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}
fileList::~fileList(){
    delete m_settingsHelper;
}
void fileList::addFiles(){
    fileDialog=new QFileDialog();
    fileDialog->setNameFilter(m_nameFilter);
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    connect(fileDialog, SIGNAL(filesSelected(QStringList)), this, SLOT(doAdd(QStringList)));
    fileDialog->exec();
    fileDialog->deleteLater();
}
void fileList::doAdd(QStringList list){
    QStringList filesToAdd;
    for (auto file : list){
        if (!m_list.contains(file)) filesToAdd << file;
    }
    this->addItems(filesToAdd);
    m_list << filesToAdd;
    m_settingsHelper->saveList(m_fileList, m_list);

}
void fileList::removeSelected(){

    for(QListWidgetItem * item : selectedItems())
    {
        delete takeItem(row(item));
    }

    m_list.clear();

    for(int i = 0; i < count(); ++i)
    {
        QListWidgetItem* itm = item(i);
        m_list << itm->text();
    }
    m_settingsHelper->saveList(m_fileList, m_list);
}
