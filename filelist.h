#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include <QListWidget>
#include <QFileDialog>

#include "clsettingshelper.h"

class fileList : public QListWidget
{
    Q_OBJECT
public:
    fileList(QWidget *parent=0, QString fileList="Null", QString nameFilter="All Files (*.*)");
    ~fileList();
    QString getFileList(){ return m_fileList; }
public slots:
    void addFiles();
    void doAdd(QStringList list);
    void removeSelected();
private:
    clSettingsHelper * m_settingsHelper;
    QString m_fileList;
    QString m_nameFilter;
    QStringList m_list;
    QFileDialog * fileDialog;

    void setColours();


};

#endif // FILELIST_H
