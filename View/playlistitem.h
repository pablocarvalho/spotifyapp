#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H
#include <QPushButton>

class PlaylistItem : public QPushButton
{
public:
    PlaylistItem(QString playlistName, QWidget* parent = nullptr);

private:
    QString name;

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
};

#endif // PLAYLISTITEM_H
