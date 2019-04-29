#ifndef PLAYLISTTRACKSAREA_H
#define PLAYLISTTRACKSAREA_H

#include <QWidget>
#include <playlisttrackwidget.h>
namespace Ui {
class PlaylistTracksArea;
}

class PlaylistTracksArea : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistTracksArea(QWidget *parent = nullptr);
    ~PlaylistTracksArea();
    void addPlaylistTrackWidget(PlaylistTrackWidget* trackwidget);
    void clearTracks();



private:
    Ui::PlaylistTracksArea *ui;

public slots:
    void updateTrackIndexes();
};

#endif // PLAYLISTTRACKSAREA_H
