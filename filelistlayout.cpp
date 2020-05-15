#include "filelistlayout.h"
#include "clsettingshelper.h"
#include <QDebug>
#include <QSettings>
#include <QList>


fileListLayout::fileListLayout(QWidget *parent, QString fileListName, QString nameFilter): QVBoxLayout(parent)
{
    m_fileList = new fileList(this->widget(), fileListName, nameFilter);
    addWidget(m_fileList);
    connect(m_fileList, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    m_addRemoveBtns = new wgtAddRemoveBtns(this->widget());
    addWidget(m_addRemoveBtns);
    connect(m_addRemoveBtns->addButton(), SIGNAL(pressed()), m_fileList, SLOT(addFiles()));
    connect(m_addRemoveBtns->removeButton(), SIGNAL(pressed()), m_fileList, SLOT(removeSelected()));
//    connect(m_addRemoveBtns->blacklistButton(), SIGNAL(pressed()), this, SLOT(onBlacklist()));
    connect(m_addRemoveBtns, SIGNAL(blacklistServers(bool)), this, SLOT(blacklistSelected(bool)));
    connect(this, SIGNAL(setBlacklistBtn(bool)), m_addRemoveBtns, SLOT(setBlacklistBtn(bool)));
    selectionChanged();

}
fileListLayout::~fileListLayout(){
    delete m_fileList;
    delete m_addRemoveBtns;
}
void fileListLayout::blacklistSelected(bool blacklist){
    if (m_fileList->selectedItems().count() > 0){
        for (QListWidgetItem *item : m_fileList->selectedItems()){
            QString server=item->text();
            if (blacklist){
                addToBlacklist(server);
                item->setForeground(Qt::red);
            } else {
                removeFromBlacklist(server);
                item->setForeground(Qt::black);
            }
        }
        QString selectedText=m_fileList->currentItem()->text();//->selectedItems().at(0)->text();
        emit setBlacklistBtn(!isBlacklisted(selectedText));
    }
}
void fileListLayout::selectionChanged(){
    m_addRemoveBtns->removeButton()->setEnabled(m_fileList->selectedItems().count() > 0);
    m_addRemoveBtns->blacklistButton()->setEnabled(m_fileList->selectedItems().count() > 0);

    if (m_fileList->selectedItems().count() > 0){
        QString selectedText=m_fileList->currentItem()->text();//->selectedItems().at(0)->text();
        emit setBlacklistBtn(!isBlacklisted(selectedText));
    }
}
void fileListLayout::addToBlacklist(QString server){
    QString f=m_blacklist();
    QStringList blacklist=clSettingsHelper::getList(f);
    if (!blacklist.contains(server)){
        blacklist.append(server);
        clSettingsHelper::saveList(f, blacklist);
    }
}
void fileListLayout::removeFromBlacklist(QString server){
    QString f=m_blacklist();
    QStringList blacklist=clSettingsHelper::getList(f);
    if (blacklist.contains(server)){
        blacklist.removeOne(server);
        clSettingsHelper::saveList(f, blacklist);
    }
}
bool fileListLayout::isBlacklisted(QString server){
    QString f=m_blacklist();
    QStringList blacklist=clSettingsHelper::getList(f);
    return blacklist.contains(server);
}

