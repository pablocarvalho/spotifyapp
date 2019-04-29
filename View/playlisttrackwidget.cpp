#include "playlisttrackwidget.h"
#include "ui_playlisttrackwidget.h"

PlaylistTrackWidget::PlaylistTrackWidget(QString id, QString name, QString previewUrl,QStringList artists,int playlistPos, QString playlistName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistTrackWidget)
{
    ui->setupUi(this);

    this->id = id;
    this->name = name;
    this->previewUrl = previewUrl;
    this->artists = artists;
    this->playlistPos = playlistPos;
    this->playlistName = playlistName;
    QString artistsField;
    for(QString artist:artists)
    {
        artistsField.append(artist);
        artistsField.append(" ");
    }
    ui->artistLabel->setText(artistsField);
    ui->trackNameLabel->setText(name);

    connect(ui->playSongPushButton,&QPushButton::released,[this]{
        emit this->playTrack(this->id,this->previewUrl);
    });

    connect(ui->removePushButton,&QPushButton::released,[this]{
        emit requestTrackRemoval(this->id, this->playlistName, this->playlistPos);
    });

}

PlaylistTrackWidget::~PlaylistTrackWidget()
{
    delete ui;
}

void PlaylistTrackWidget::setPlaylistPos(int playlistPos){
    this->playlistPos = playlistPos;
}
