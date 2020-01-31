#ifndef DLGGETUSERINPUT_H
#define DLGGETUSERINPUT_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class dlgGetUserInput;
}

class dlgGetUserInput : public QDialog
{
    Q_OBJECT

public:
    explicit dlgGetUserInput(QWidget *parent = 0);
    ~dlgGetUserInput();
    QString text() { return m_text->text(); }
private:
    Ui::dlgGetUserInput *ui;
    QLineEdit * m_text;
};

#endif // DLGGETUSERINPUT_H
