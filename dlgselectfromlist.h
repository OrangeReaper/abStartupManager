#ifndef DLGSELECTFROMLIST_H
#define DLGSELECTFROMLIST_H

#include <QDialog>
#include <QString>
#include <QComboBox>

namespace Ui {
class dlgSelectFromList;
}

class dlgSelectFromList : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSelectFromList(QWidget *parent = 0, QStringList list=QStringList());
    ~dlgSelectFromList();
    QString selectedItem() { return m_combobox->currentText(); }

private:
    Ui::dlgSelectFromList *ui;
    QComboBox * m_combobox;
};

#endif // DLGSELECTFROMLIST_H
