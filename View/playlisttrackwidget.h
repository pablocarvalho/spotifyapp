#ifndef PLAYLISTTRACKWIDGET_H
#define PLAYLISTTRACKWIDGET_H

#include <QWidget>

namespace Ui {
class PlaylistTrackWidget;
}

class PlaylistTrackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistTrackWidget(QString id, QString name, QString previewUrl,QStringList artists,int playlistPos,QString playlistName,QWidget *parent = nullptr);
    ~PlaylistTrackWidget();

    void setPlaylistPos(int);

private:
    Ui::PlaylistTrackWidget *ui;

    QString name;
    QString id;
    QString previewUrl;
    QStringList artists;
    int playlistPos;
    QString playlistName;

signals:
    void playTrack(QString id, QString previewUrl);
    void requestTrackRemoval(QString trackId, QString playlistName, int trackPosition);



};

#endif // PLAYLISTTRACKWIDGET_H
