#ifndef SONG_H
#define SONG_H

#include <QString>
#include <QStringList>
class Track
{
public:
    Track(QString id, QString name, QStringList artists, QString previewUrl);
    Track();

    QString getId() const;
    QString getName() const;
    QStringList getArtists() const;
    QString getPreviewUrl() const;



private:
    QString id;
    QString name;
    QStringList artists;
    QString previewUrl;

};

QDataStream &operator<<(QDataStream &, const Track &);
QDataStream &operator>>(QDataStream &, Track &);

#endif // SONG_H
