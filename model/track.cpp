#include "track.h"
#include <QDataStream>
Track::Track()
{

}
Track::Track(QString id, QString name, QStringList artists, QString previewUrl)
{
    this->id = id;
    this->name = name;
    this->artists = artists;
    this->previewUrl = previewUrl;
}

QString Track::getId() const
{
    return id;
}
QString Track::getName() const
{
    return name;
}

QStringList Track::getArtists() const
{
    return artists;
}

QString Track::getPreviewUrl() const{
    return previewUrl;
}

QDataStream &operator<<(QDataStream &out, const Track &track)
{
    out << track.getId();
    out << track.getName();
    out << track.getArtists();
    out << track.getPreviewUrl();
    return out;
}

QDataStream &operator>>(QDataStream &in, Track &track)
{
    QString id, name, previewUrl;
    QStringList artists;

    in >> id;
    in >> name;
    in >> artists;
    in >> previewUrl;

    track = Track(id,name,artists,previewUrl);
    return in;
}
