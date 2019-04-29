#include "playlistitem.h"

PlaylistItem::PlaylistItem(QString name, QWidget* parent) : QPushButton (parent)
{
    this->name = name;
    setText(name);
    setFlat(true);
    this->setStyleSheet("color:rgb(136, 138, 133);text-align:left");
//    setFocus(Qt::no)
}


void PlaylistItem::enterEvent(QEvent *event){

    setStyleSheet("color:rgb(211, 215, 207);text-align:left");
    QWidget::enterEvent(event);

}
void PlaylistItem::leaveEvent(QEvent *event){

    setStyleSheet("color:rgb(136, 138, 133);text-align:left");
    QWidget::leaveEvent(event);

}
