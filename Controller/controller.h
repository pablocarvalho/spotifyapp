#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "controller_global.h"
#include <session.h>
#include <QObject>
#include "../View/playlisttrackwidget.h"

#include <QOAuth2AuthorizationCodeFlow>
#include <QDir>

class CONTROLLERSHARED_EXPORT Controller : public QObject
{
    Q_OBJECT
private:
    static bool instanceFlag;
    static Controller *instance;
    Controller();

    Session session;
    QOAuth2AuthorizationCodeFlow authorization;

    void getUserInfo();
    void queryTrack(QString trackId);

    void persistPlaylist();

    void configUserEnvironment();
    void loadUserPlaylists();


    static const QString DATA_FOLDER;

public:
    static Controller* getInstance();
    void startSession();
    QString getSessionToken();

    void searchTrack(QString name);
    QString getUserName();
    QStringList getPlaylistsNames();

    void addSongToUserPlaylist(QString playlist, QString trackId, QString trackName, QStringList trackArtists, QString previewUrl);
    QList<PlaylistTrackWidget*>* configurePlaylistTrackWidget(QString playlistName);


private slots:
    void granted();
    void authStatusChanged (QAbstractOAuth::Status status);



signals:
    void connectionStablished();
    void foundTrack(QString name, QStringList artists, QString id, QString previewUrl);
    void playlistCreated(QString);
    void updateTracksWidgetIndexes();

public slots:
    void createPlaylist(QString name);
    void removeTrackFromPlaylist(QString trackId, QString playlistName, int trackPosition);

};

#endif // CONTROLLER_H
