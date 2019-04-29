#ifndef USER_H
#define USER_H

#include <QString>
#include "playlist.h"
#include <QSharedPointer>
class User
{
public:
    User(QString id,QString displayName);
    User();

    QString getDisplayName();
    void addPlaylist(Playlist newPlaylist);
    void addTrackToPlaylist(Track newTrack,QString playlistName, QDataStream& out);
    void removeTrackFromPlaylist(int trackPos,QString playlistName, QDataStream& out);
    QList<Playlist>* getPlaylists() const;
    QString getId();
    void loadPlaylist(QDataStream &);
    static const QString USER_FILE_FORMAT;

private:
    QString id;
    QString displayName;
    QSharedPointer<QList<Playlist>> playlists;


};

#endif // USER_H
