#ifndef ABUIIMAGE_H
#define ABUIIMAGE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMenu>

class abUIImage : public QLabel
{
    Q_OBJECT
public:
    explicit abUIImage(QWidget *parent = nullptr, QString imagePath="", int height=100, int width=100);
    void loadImage(QString imagePath);
    virtual void resize(int w, int h);
    QMenu * menu(){ return m_menu; }
signals:

public slots:
    void ShowContextMenu(const QPoint &pos);
private:
    void S_LoadImageFromQPixmap(QPixmap img);
    void loadImageFromQPixmap(QPixmap img);
    void loadImageFromQImage(QImage qimg);
    void setMenu();

    QString m_imagePath;

    QMenu * m_menu;
};

#endif // ABUIIMAGE_H
