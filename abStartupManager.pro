#-------------------------------------------------
#
# Project created by QtCreator 2020-01-22T13:36:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = abStartupManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    SmtpClient/src/emailaddress.cpp \
    SmtpClient/src/mimeattachment.cpp \
    SmtpClient/src/mimecontentformatter.cpp \
    SmtpClient/src/mimefile.cpp \
    SmtpClient/src/mimehtml.cpp \
    SmtpClient/src/mimeinlinefile.cpp \
    SmtpClient/src/mimemessage.cpp \
    SmtpClient/src/mimemultipart.cpp \
    SmtpClient/src/mimepart.cpp \
    SmtpClient/src/mimetext.cpp \
    SmtpClient/src/quotedprintable.cpp \
    SmtpClient/src/smtpclient.cpp \
    abfunctions.cpp \
    abuiimage.cpp \
    clVPNInterface.cpp \
    clsettings.cpp \
    clsettingshelper.cpp \
    connecttovpn.cpp \
    dlgruncliapp.cpp \
    dlgsettings.cpp \
    filelist.cpp \
    filelistlayout.cpp \
    generalsettingslayout.cpp \
    main.cpp \
    mainwindow.cpp \
    wgtaddremovebtns.cpp \
    wgtsetting.cpp \
    mailer.cpp \
    dlgselectfromlist.cpp \
    dlggetuserinput.cpp \
    abqaction.cpp

HEADERS += \
    mainwindow.h \
    SmtpClient/src/SmtpMime \
    SmtpClient/src/emailaddress.h \
    SmtpClient/src/mimeattachment.h \
    SmtpClient/src/mimecontentformatter.h \
    SmtpClient/src/mimefile.h \
    SmtpClient/src/mimehtml.h \
    SmtpClient/src/mimeinlinefile.h \
    SmtpClient/src/mimemessage.h \
    SmtpClient/src/mimemultipart.h \
    SmtpClient/src/mimepart.h \
    SmtpClient/src/mimetext.h \
    SmtpClient/src/quotedprintable.h \
    SmtpClient/src/smtpclient.h \
    SmtpClient/src/smtpexports.h \
    abfunctions.h \
    abuiimage.h \
    clVPNInterface.h \
    clsettings.h \
    clsettingshelper.h \
    connecttovpn.h \
    dlgruncliapp.h \
    dlgsettings.h \
    filelist.h \
    filelistlayout.h \
    generalsettingslayout.h \
    wgtaddremovebtns.h \
    wgtsetting.h \
    mailer.h \
    dlgselectfromlist.h \
    dlggetuserinput.h \
    abqaction.h

FORMS += \
    mainwindow.ui \
    dlgsettings.ui \
    wgtsetting.ui \
    wgtaddremovebtns.ui \
    dlgruncliapp.ui \
    abmessagebox.ui \
    dlgselectfromlist.ui \
    dlggetuserinput.ui

DISTFILES +=

RESOURCES += \
    abstartupmanager.qrc \
    images.qrc
