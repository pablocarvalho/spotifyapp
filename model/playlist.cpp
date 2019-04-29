#include "playlist.h"
#include <QDataStream>

const QString Playlist::PLAYLIST_FILE_FORMAT = ".plt";

Playlist::Playlist()
{

}

Playlist::Playlist(QString name){
    this->name = name;
}

Playlist::Playlist(QString name, QList<Track> tracks)
{
    this->name = name;
    this->tracks = tracks;
}

QString Playlist::getName(){
    return name;
}

void Playlist::addTrack(Track newTrack){
    tracks.append(newTrack);
}

QList<Track> Playlist::getTracks() const{
    return tracks;
}

QDataStream &operator<<(QDataStream & out , Playlist & playlist){

    out << playlist.getName();
    out << playlist.getTracks();

    return out;

}

QDataStream &operator>>(QDataStream & in , Playlist & playlist)
{
    QList<Track> tracks;
    QString name;
    in >> name;
    in >> tracks;
    playlist = Playlist(name,tracks);
    return in;
}

void Playlist::removeTrack(int pos){
    tracks.removeAt(pos);
}
