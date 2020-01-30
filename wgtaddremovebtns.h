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
private:
    Ui::wgtAddRemoveBtns *ui;
    QToolButton *  m_addButton;
    QToolButton *  m_removeButton;
};

#endif // WGTADDREMOVEBTNS_H
