#ifndef GENERALSETTINGSLAYOUT_H
#define GENERALSETTINGSLAYOUT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

class generalSettingsLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    generalSettingsLayout(QWidget *parent=0);
    ~generalSettingsLayout();
private:
    bool ignore(QString setting);
};

#endif // GENERALSETTINGSLAYOUT_H

