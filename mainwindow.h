#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMainWindow>
#include <QSettings>
#include <QProcess>
#include <QThread>

#include "connecttovpn.h"
#include "clpingtestvpn.h"
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

public slots:
    void settings();
    void status();
    void shutdown();
    void cancelShutdown();
    void vpnConnected();
    void pingStateChanged(bool isConnected);
    void runShutdownCmd();
    void userClose(QMessageBox::StandardButton reply=QMessageBox::NoButton);
    void populateProfileMenu();
    void selectProfile(QString text);
    void failedToConnect();
    void logSomething(QString logEntry);
    void enable();
    void disable();
private:
    Ui::MainWindow *ui;
    void vpnEnabled(bool enable);
    void connect_vpn(QString openVPNCmd, QString ovpnFile, QString authFile);
    void runStartupApps();
    void runCmdDetached(QProcess * p,QString cmd);
    void doConnect();
    void logDisconnection();
    void emailServerFailures();
    void saveWindowState();
    void disconnectVPN();
    void disconnectKillSwitch();
    void connectKillSwitch();


    bool monitoring=false;
    bool switching=false;
    bool m_connected=false;
    bool m_connecting=false;
    bool m_reportDisconnect=false;
    bool m_shutdownCancelled=false;

    int nextVPNConnection=0;

    connectToVPN * m_connectToVPN = nullptr;
    abUIImage * pgmImage;
    clpingtestvpn * pingTestVPN;

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

    QAction * a_disable;
    QAction * a_enable;

    QProcess * p_NoKillSwitch=0;
    QProcess * p_KillSwitch=0;
};

#endif // MAINWINDOW_H
