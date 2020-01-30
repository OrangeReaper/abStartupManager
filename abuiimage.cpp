#include "abuiimage.h"

abUIImage::abUIImage(QWidget *parent, QString imagePath, int height, int width) : QLabel(parent)
{
    m_imagePath=imagePath;
    resize(width, height);

}
void abUIImage::resize(int w, int h){
    QLabel::resize(w,h);
    loadImage(m_imagePath);
    setMenu();
}

void abUIImage::loadImage(QString imagePath){
    loadImageFromQImage(QImage(imagePath));//QImage(":/images/image1.jpg")
}
void abUIImage::loadImageFromQImage( QImage qimg){
    QPixmap img=QPixmap::fromImage(qimg);
    loadImageFromQPixmap(img);
}
void abUIImage::loadImageFromQPixmap(QPixmap img){
    if (!img.isNull()){
        S_LoadImageFromQPixmap(img);
    }
}
void abUIImage::S_LoadImageFromQPixmap( QPixmap img){
    if (!img.isNull()){
       setPixmap(img.scaled(width(),height(),
            Qt::AspectRatioMode::IgnoreAspectRatio,
            Qt::TransformationMode::SmoothTransformation));
    }
}
void abUIImage::setMenu(){
    //Context Menu setup
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));

    m_menu = new QMenu(this);

    QString  menuStyle(
             "QMenu::item{"
             "background-color: rgb(0, 0, 0);"
             "color: rgb(255, 255, 255);"
             "}"
             "QMenu::item:selected{"
             "background-color: rgb(0, 85, 127);"
             "color: rgb(255, 255, 255);"
             "}"
          );

    m_menu->setStyleSheet(menuStyle);

}
void abUIImage::ShowContextMenu(const QPoint &pos){
    m_menu->exec(mapToGlobal(pos));
}
