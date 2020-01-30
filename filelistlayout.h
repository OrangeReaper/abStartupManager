#ifndef FILELISTLAYOUT_H
#define FILELISTLAYOUT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

#include "filelist.h"
#include "wgtaddremovebtns.h"

class fileListLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    fileListLayout(QWidget *parent=0, QString fileListName="Null", QString nameFilter="All Files (*.*)");
    ~fileListLayout();
public slots:
    void selectionChanged();
private:
    fileList            * m_fileList;
    wgtAddRemoveBtns    * m_addRemoveBtns;
};

#endif // FILELISTLAYOUT_H
