#include "searchresultwidget.h"
#include "ui_searchresultwidget.h"
#include <QDebug>
SearchResultWidget::SearchResultWidget(QString name, QStringList artists, QString id, QString previewUrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResultWidget)
{
    ui->setupUi(this);

    this->name = name;
    this->artists = artists;
    this->id = id;
    this->previewUrl = previewUrl;

    QString artistsString;
    for(QString str : artists)
    {
        artistsString.append(str);
        artistsString.append(" ");
    }

    ui->artistLabel->setText(artistsString);
    ui->songNameLabel->setText(name);

    connect(ui->playSongPushButton, &QPushButton::released, [this](){
        emit playTrack(this->id,this->previewUrl);
    });

    connect(ui->addToPlaylistPushButton,&QPushButton::released, [this](){

        emit requestPlaylistsContextMenu(this);
    });

}

SearchResultWidget::~SearchResultWidget()
{
    delete ui;
}

void SearchResultWidget::showPlaylistContextMenu(QMenu * menu){

    ui->addToPlaylistPushButton->setMenu(menu);
    ui->addToPlaylistPushButton->showMenu();

    ui->addToPlaylistPushButton->setMenu(nullptr);
}

void SearchResultWidget::playlistSelected(){
    QAction* action = qobject_cast<QAction*>(sender());

    if(action){
        this->playlistName = action->text();
    }

}

QString SearchResultWidget::getName(){
    return name;
}

QStringList SearchResultWidget::getArtists(){
    return artists;
}
QString SearchResultWidget::getId(){
    return id;
}
QString SearchResultWidget::getPreviewUrl(){
    return previewUrl;
}
QString SearchResultWidget::getPlaylistName(){
    QString returnvar = playlistName;
    playlistName = "";
    return returnvar;

}
