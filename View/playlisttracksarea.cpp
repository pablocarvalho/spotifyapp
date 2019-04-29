#include "playlisttracksarea.h"
#include "ui_playlisttracksarea.h"

PlaylistTracksArea::PlaylistTracksArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistTracksArea)
{
    ui->setupUi(this);
}

PlaylistTracksArea::~PlaylistTracksArea()
{
    delete ui;
}

void PlaylistTracksArea::addPlaylistTrackWidget(PlaylistTrackWidget* trackWidget)
{
    trackWidget->setParent(this);
    ui->verticalLayout->addWidget(trackWidget);
}

void PlaylistTracksArea::clearTracks()
{

    QList<PlaylistTrackWidget *> widgets = findChildren<PlaylistTrackWidget *>();
    foreach(PlaylistTrackWidget * widget, widgets)
    {
        delete widget;
    }
}

void PlaylistTracksArea::updateTrackIndexes(){
    QList<PlaylistTrackWidget *> widgets = findChildren<PlaylistTrackWidget *>();
    int index = 0;
    foreach(PlaylistTrackWidget * widget, widgets)
    {
        widget->setPlaylistPos(index);
        ++index;
    }

}
