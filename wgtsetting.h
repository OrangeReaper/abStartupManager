#ifndef WGTSETTING_H
#define WGTSETTING_H

#include <QWidget>

namespace Ui {
class wgtSetting;
}

class wgtSetting : public QWidget
{
    Q_OBJECT

public:
    explicit wgtSetting(QWidget *parent = 0, QString setting="null", QString value="null");
    ~wgtSetting();
public slots:
    void onAction();
    void onCancel();
private:
    Ui::wgtSetting *ui;

    void setMode(bool editing);
    void updateValue();
    void showSetting();

    bool m_editing =  false;

    QString m_setting;
    QString m_value;
};

#endif // WGTSETTING_H
