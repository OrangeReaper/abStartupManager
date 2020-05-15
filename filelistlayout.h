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
    static bool isBlacklisted(QString server);
    static void addToBlacklist(QString server);
    static void removeFromBlacklist(QString server);
public slots:
    void selectionChanged();
    void blacklistSelected(bool blacklist);
signals:
    void setBlacklistBtn(bool setBlacklistBtn);
private:
    fileList            * m_fileList;
    wgtAddRemoveBtns    * m_addRemoveBtns;
    static QString m_blacklist(){return "Blacklist"; }

};

#endif // FILELISTLAYOUT_H
