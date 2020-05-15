#ifndef WGTADDREMOVEBTNS_H
#define WGTADDREMOVEBTNS_H

#include <QWidget>
#include <QToolButton>

namespace Ui {
class wgtAddRemoveBtns;
}

class wgtAddRemoveBtns : public QWidget
{
    Q_OBJECT

public:
    explicit wgtAddRemoveBtns(QWidget *parent = 0);
    ~wgtAddRemoveBtns();
    QToolButton * addButton(){ return m_addButton; }
    QToolButton * removeButton(){ return m_removeButton; }
    QToolButton * blacklistButton(){ return m_blacklistButton; }
public slots:
    void onBlacklistButton();
    void setBlacklistBtn(bool blacklist);
signals:
    void  blacklistServers(bool blacklist);
private:
    Ui::wgtAddRemoveBtns *ui;
    QToolButton *  m_addButton;
    QToolButton *  m_removeButton;
    QToolButton *  m_blacklistButton;
    bool m_blacklist=true;
    void setBlacklistButton();
};

#endif // WGTADDREMOVEBTNS_H
