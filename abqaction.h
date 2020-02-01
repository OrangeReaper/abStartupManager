#ifndef ABQACTION_H
#define ABQACTION_H

#include <QObject>
#include <QWidget>
#include <QAction>

class abQAction : public QAction
{
    Q_OBJECT
public:
    explicit abQAction(QString text, QObject *parent = nullptr);

signals:
    void triggered(QString text);
public slots:
    void emitTriggered();
};

#endif // ABQACTION_H
