#include "controller.h"
#include <QtNetworkAuth>
#include <QDesktopServices>
#include <query.h>
#include "../View/playlisttrackwidget.h"

bool Controller::instanceFlag = false;
Controller* Controller::instance = nullptr;
const QString Controller::DATA_FOLDER = "data";

Controller::Controller()
{
}

Controller* Controller::getInstance()
{
    if(! instanceFlag)
    {
        instance = new Controller();
        instanceFlag = true;
    }
    return instance;
}

void Controller::startSession(){
    auto replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
    authorization.setReplyHandler(replyHandler);
    authorization.setAuthorizationUrl(QUrl(Query::autorizationUrl));
    authorization.setAccessTokenUrl(QUrl(Query::accessTokenUrl));
    authorization.setClientIdentifier("2905243a797a44b9afa9071d7a3bd1c8");
    authorization.setClientIdentifierSharedKey("0cc3061bd2314e269038c24397c4ec73");
//    authorization.setScope("user-read-private user-top-read playlist-read-private playlist-modify-public playlist-modify-private user-read-email user-read-birthdate streaming user-read-playback-state user-modify-playback-state");
    authorization.setScope("user-read-birthdate user-read-private user-read-email");
    connect(&authorization, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
             &QDesktopServices::openUrl);

    connect(&authorization, &QOAuth2AuthorizationCodeFlow::statusChanged,
            this, &Controller::authStatusChanged);

    connect(&authorization, &QOAuth2AuthorizationCodeFlow::granted,
            this, &Controller::granted);

    authorization.grant();
}

void Controller::granted ()
{
    qDebug()<<"Signal granted received";

    QString token = authorization.token();
    qDebug()<<"Token: " << token;

    session.setToken(token);

    getUserInfo();

}

void Controller::authStatusChanged(QAbstractOAuth::Status status)
{
    QString s;
    if (status == QAbstractOAuth::Status::Granted)
        s = "granted";

    if (status == QAbstractOAuth::Status::TemporaryCredentialsReceived) {
        s = "temp credentials";
    }

    qDebug()<<"Auth Status changed: " << s;
}

void Controller::getUserInfo(){
    qDebug()<<"Loading User Informations";

    QUrl u (Query::userInfoUrl);

    auto reply = authorization.get(u);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug()<<reply->errorString();
            return;
        }
        const auto data = reply->readAll();

        const auto document = QJsonDocument::fromJson(data);
        const auto root = document.object();
        QString id = root.value("id").toString();
        QString displayName = root.value("display_name").toString();

        User user(id,displayName);

        session.setUser(user);

        reply->deleteLater();

        configUserEnvironment();
        emit connectionStablished();


    });

}

QString Controller::getSessionToken(){
    return session.getToken();
}


void Controller::searchTrack(QString songName){

    QUrl u (Query::trackSeach(songName.split(" "),"BR"));
    auto reply = authorization.get(u);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug()<<reply->errorString();
            return;
        }
        const auto data = reply->readAll();
        const auto document = QJsonDocument::fromJson(data);
        QJsonObject responseObject = document.object().value("tracks").toObject();

        QJsonArray tracksArray = responseObject.value("items").toArray();

        for(auto item : tracksArray)
        {
            QJsonObject track = item.toObject();
            QString id = track.value("id").toString();
            queryTrack(id);
        }

        reply->deleteLater();
    });
}

void Controller::queryTrack(QString trackId){
     QString url = Query::trackQuery(trackId,"BR");
     QUrl u (url);
     auto reply = authorization.get(u);

     connect(reply, &QNetworkReply::finished, [=]() {

         if (reply->error() != QNetworkReply::NoError) {
             qDebug()<<reply->errorString();
             return;
         }

         const auto data = reply->readAll();
         const auto document = QJsonDocument::fromJson(data);
         QJsonObject responseObject = document.object();
         QString ext = responseObject.value("preview_url").toString();
        QString trackName = responseObject.value("name").toString();
            QStringList artists;
         QJsonArray artistsArray = responseObject.value("artists").toArray();

         for(auto artist : artistsArray)
         {
             QString name = artist.toObject().value("name").toString();
             artists.append(name);
         }

        qDebug()<<trackName << "\t" << artists << "\t" << trackId << "\t" << ext;
        emit foundTrack(trackName,artists,trackId,ext);


     });
}

QString Controller::getUserName()
{
    return session.getUser().getDisplayName();
}

void Controller::createPlaylist(QString name)
{
    Playlist newPlaylist(name);
    session.getUser().addPlaylist(newPlaylist);
    emit playlistCreated(name);
}

QStringList Controller::getPlaylistsNames()
{
    QStringList answer;

    QList<Playlist>* playlists = session.getUser().getPlaylists();
    for(Playlist playlist : *playlists ){
        answer.append(playlist.getName());

    }

    return answer;

}

void Controller::addSongToUserPlaylist(QString playlist, QString trackId, QString trackName, QStringList trackArtists, QString previewUrl)
{
    Track newTrack(trackId,trackName,trackArtists,previewUrl);
    QString fileName = Controller::DATA_FOLDER + "/" + session.getUser().getId() + "/" + playlist + Playlist::PLAYLIST_FILE_FORMAT;
    QFile file(fileName);
    file.open(QFile::WriteOnly);
    QDataStream writeStream(&file);
    session.getUser().addTrackToPlaylist(newTrack,playlist,writeStream);
    file.close();
}

void Controller::configUserEnvironment()
{
    QString folder = Controller::DATA_FOLDER;
    QDir dataFolder(folder);
    dataFolder.setPath(QDir::currentPath());
    bool answer = QDir(folder).exists();
    if(!answer)
        dataFolder.mkpath(Controller::DATA_FOLDER);
    QDir userFolder(Controller::DATA_FOLDER + "/"+session.getUser().getId());
    bool folderExists = userFolder.exists();
    if(!folderExists)
        dataFolder.mkdir(Controller::DATA_FOLDER + "/" +session.getUser().getId());

    loadUserPlaylists();
}

void Controller::loadUserPlaylists()
{
    QDir userFolder(Controller::DATA_FOLDER + "/"+session.getUser().getId());
    QString playlistfilter = "*"+Playlist::PLAYLIST_FILE_FORMAT;
    QStringList playlistFiles = userFolder.entryList(QStringList() << playlistfilter,QDir::Files);

    for(QString filename : playlistFiles )
    {
        QString folder = userFolder.absoluteFilePath(filename);
        QFile playlistFile(folder);
        QString playlistName = filename.remove(Playlist::PLAYLIST_FILE_FORMAT);
        playlistFile.open(QFile::ReadOnly);
        QDataStream loadStream(&playlistFile);
        session.getUser().loadPlaylist(loadStream);
        playlistFile.close();
        emit playlistCreated(playlistName);
    }
}

QList<PlaylistTrackWidget*>* Controller::configurePlaylistTrackWidget(QString playlistName){


    QList<PlaylistTrackWidget*>* answerList = new QList<PlaylistTrackWidget*>();
    QList<Playlist>* userPlaylists = session.getUser().getPlaylists();

    for(Playlist playlist : *userPlaylists)
    {

        if(playlist.getName() == playlistName){

            QList<Track> tracks = playlist.getTracks();

            for(int i = 0; i < tracks.size(); ++i){
                Track track = tracks.at(i);
                PlaylistTrackWidget* trackwidget = new PlaylistTrackWidget(track.getId(),track.getName(),track.getPreviewUrl(),track.getArtists(),i,playlist.getName());
                answerList->append(trackwidget);
            }
        }
    }

    return answerList;

}

void Controller::removeTrackFromPlaylist(QString trackId, QString playlistName, int trackPosition){

    PlaylistTrackWidget* trackWidget = dynamic_cast<PlaylistTrackWidget*>(sender());
    QString fileName = Controller::DATA_FOLDER + "/" + session.getUser().getId() + "/" + playlistName + Playlist::PLAYLIST_FILE_FORMAT;
    QFile file(fileName);
    file.open(QFile::WriteOnly);
    QDataStream writeStream(&file);
    session.getUser().removeTrackFromPlaylist(trackPosition,playlistName,writeStream);
    delete trackWidget;
    emit updateTracksWidgetIndexes();

}
