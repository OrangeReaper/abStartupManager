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
    explicit dlgRunCLIApp(QWidget *parent = 0, QProcess * process = nullptr, QString command="", bool userCanAbort=true, bool runDetached=false, QStringList abort=QStringList());
    ~dlgRunCLIApp();

protected:
      void closeEvent(QCloseEvent *event);

public slots:
    void abortProcess();
    void readyReadStandardOutput();
    void saveLog();
signals:
    void abort();

private:
    Ui::dlgRunCLIApp *ui;
    QProcess * m_process;
    QStringList m_abort;
    bool aborting=false;
    void abortProcess(QString line);

    bool logSaved=false;
};

#endif // DLGRUNCLIAPP_H
