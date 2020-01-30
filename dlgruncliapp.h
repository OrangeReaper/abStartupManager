#ifndef DLGRUNCLIAPP_H
#define DLGRUNCLIAPP_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class dlgRunCLIApp;
}

class dlgRunCLIApp : public QDialog
{
    Q_OBJECT

public:
    explicit dlgRunCLIApp(QWidget *parent = 0, QProcess * process = nullptr, QString command="", bool userCanAbort=true, bool runDetached=false);
    ~dlgRunCLIApp();
public slots:
    void abortProcess();
    void readyReadStandardOutput();

private:
    Ui::dlgRunCLIApp *ui;
    QProcess * m_process;
};

#endif // DLGRUNCLIAPP_H
