#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>
#include "generalsettingslayout.h"
#include "filelistlayout.h"

namespace Ui {
class dlgSettings;
}

class dlgSettings : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSettings(QWidget *parent = 0);
    ~dlgSettings();

private:
    Ui::dlgSettings *ui;

    generalSettingsLayout * m_generalSettingsLayout;
    fileListLayout * m_serverList;
};

#endif // DLGSETTINGS_H
