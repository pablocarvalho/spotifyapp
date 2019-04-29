#ifndef PLAYLISTAREA_H
#define PLAYLISTAREA_H
#include "playlistitem.h"
#include <QWidget>

namespace Ui {
class PlaylistArea;
}

class PlaylistArea : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistArea(QWidget *parent = nullptr);    
    ~PlaylistArea();
    PlaylistItem* addPlaylist(QString name);

private:
    Ui::PlaylistArea *ui;

private slots:
    void newPlaylistRequest();

signals:
    void requestPlaylistCreation(QString);
};

#endif // PLAYLISTAREA_H
