#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include "track.h"

class Playlist
{
public:
    Playlist();
    Playlist(QString name);
    Playlist(QString name,QList<Track> tracks);
    void addTrack(Track newTrack);
    void removeTrack(int pos);
    QList<Track> getTracks() const;
    QString getName();
    static const QString PLAYLIST_FILE_FORMAT;

private:
    QString name;
    QList<Track> tracks;
};

QDataStream &operator<<(QDataStream &, Playlist &);
QDataStream &operator>>(QDataStream &, Playlist &);

#endif // PLAYLIST_H
