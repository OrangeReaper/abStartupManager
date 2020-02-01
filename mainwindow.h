#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMainWindow>
#include <QSettings>
#include <QProcess>
#include <QTimer>
#include <QThread>

#include "connecttovpn.h"
#include "clVPNInterface.h"
#include "dlgruncliapp.h"
#include "abuiimage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static QString defaultProfile() { return "Default"; }

protected:
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
      void closeEvent(QCloseEvent *event);

public slots:
    void settings();
    void status();
    void shutdown();
    void vpnConnected(bool isConnected);
    void vpnAlarm();
    void runShutdownCmd();
    void userClose();
    void populateProfileMenu();
    void selectProfile(QString text);
private:
    Ui::MainWindow *ui;



    void connect_vpn(QString openVPNCmd, QString ovpnFile, QString authFile);
    void startPollingVPNInterface();
    void runStartupApps();
    void runCmdDetached(QProcess * p,QString cmd);
    void doConnect();
    void logDisconnection();
    void emailServerFailures();
    void logSomething(QString logEntry);

    bool monitoring=false;
    bool switching=false;
    bool m_closing=false;
    bool m_reportDisconnect=false;

    int nextVPNConnection=0;

    connectToVPN * m_connectToVPN = nullptr;
    clVPNInterface * vpnInterface;
    abUIImage * pgmImage;

    QTimer * VPNTimer;
    QPoint m_pos; // For moving window without titlebar

    QProcess * startUpProcess=nullptr;
    QProcess * shutdownProcess=nullptr;
    QProcess * shutdownCmdProcess=nullptr;

    QStringList m_connectionLog;
    QString m_currentProfile;
    QString getConnectionName();
    QString nextConnection();

    dlgRunCLIApp * m_shutdownCmdStatus = nullptr;

    QMenu * m_profile = nullptr;


};

#endif // MAINWINDOW_H
