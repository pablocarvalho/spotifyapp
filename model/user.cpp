#include "user.h"


const QString USER_FILE_FORMAT = ".usr";
User::User(QString id, QString displayName)
{
    this->id = id;
    this->displayName = displayName;
    playlists =  QSharedPointer<QList<Playlist>>(new QList<Playlist> );
}

User::User(){
    playlists = QSharedPointer<QList<Playlist>>(new QList<Playlist> );
}

QString User::getDisplayName(){
    return displayName;
}

void User::addPlaylist(Playlist newPlaylist)
{
    playlists->append(newPlaylist);
}

QList<Playlist>* User::getPlaylists() const
{
    return playlists.get();
}

void User::addTrackToPlaylist(Track newTrack, QString playlistName, QDataStream& out){

    if(!playlistName.isEmpty()){
        for(auto it = playlists->begin(); it != playlists->end(); ++it){

            if((*it).getName() == playlistName){
                Playlist* playlist = &(*it);
                playlist->addTrack(newTrack);
                out << *playlist;
            }
        }
    }
}

void User::removeTrackFromPlaylist(int trackPos, QString playlistName, QDataStream& out){

    if(!playlistName.isEmpty()){
        for(auto it = playlists->begin(); it != playlists->end(); ++it){

            if((*it).getName() == playlistName){
                Playlist* playlist = &(*it);
                playlist->removeTrack(trackPos);
                out << *playlist;
            }
        }
    }
}

QString User::getId(){
    return id;
}

void User::loadPlaylist(QDataStream & in){
    Playlist loadedPlaylist;
    in >> loadedPlaylist;
    playlists->append(loadedPlaylist);
}
