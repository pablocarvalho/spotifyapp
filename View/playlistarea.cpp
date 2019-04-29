#include "playlistarea.h"
#include "ui_playlistarea.h"
#include "newplaylistdialog.h"
PlaylistArea::PlaylistArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistArea)
{
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignTop);
    connect(ui->newPlaylistPushButton,&QPushButton::released,this,&PlaylistArea::newPlaylistRequest);
}

PlaylistArea::~PlaylistArea()
{
    delete ui;
}

PlaylistItem* PlaylistArea::addPlaylist(QString name)
{
    PlaylistItem* newItem = new PlaylistItem(name);
//    newItem->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    ui->verticalLayout->addWidget(newItem);

    return newItem;
}

void PlaylistArea::newPlaylistRequest(){

    NewPlaylistDialog dialog;
    int answer = dialog.exec();

    if(answer == QDialog::Accepted){
        QString playlistName = dialog.getNewPlaylistName();
        if(!playlistName.isEmpty())
            emit requestPlaylistCreation(playlistName);
    }
}
