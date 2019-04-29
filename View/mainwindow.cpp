#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QUrl>

#include <QString>
#include <QByteArray>
#include <QWebEngineSettings>
#include <QStandardPaths>
#include <QWebEngineProfile>
#include <QTimer>
#include <QString>
#include <QWebEngineCookieStore>
#include <QMouseEvent>
#include <playlistitem.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    showMaximized();
    controller = Controller::getInstance();
    connect(controller,&Controller::connectionStablished,this,&MainWindow::customizeInterface);
    connect(ui->searchButton,&QPushButton::released,this, &MainWindow::searchSongRequest);
    connect(controller,&Controller::foundTrack,this,&MainWindow::addSearchResult);
    connect(ui->playlistsArea,&PlaylistArea::requestPlaylistCreation,controller,&Controller::createPlaylist);
    connect(controller,&Controller::playlistCreated,this,&MainWindow::activatePlaylistActions);
    connect(controller,&Controller::updateTracksWidgetIndexes,ui->playlistTracksArea,&PlaylistTracksArea::updateTrackIndexes);
    controller->startSession();

    ui->browser->setContextMenuPolicy(Qt::NoContextMenu);
    ui->statusLabel->hide();

    setMouseTracking(true);
    ui->browser->setHtml("<!DOCTYPE html><html><head><style>body {background-color: #000000}</style></head></html>");
    ui->browser->setMouseTracking(true);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);

    playlistMenu = new QMenu(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::customizeInterface()
{
    ui->usernameLabel->setText(controller->getUserName());
    QString token = controller->getSessionToken();


}

void MainWindow::searchSongRequest()
{
    ui->searchResultsArea->show();
    ui->playlistTracksArea->hide();
    QString search = ui->searchLineEdit->text();
    ui->searchResultsArea->clearResults();
    controller->searchTrack(search);
    ui->statusLabel->show();
    QString status = "Results for: " + search;
    ui->statusLabel->setText(status);
}


void MainWindow::addSearchResult(QString name, QStringList artist, QString id, QString previewUrl)
{
    SearchResultWidget* result = new SearchResultWidget(name,artist,id,previewUrl);


    ui->searchResultsArea->addResult(result);
    connect(result,&SearchResultWidget::playTrack,this,&MainWindow::playTrack);
    connect(result,&SearchResultWidget::requestPlaylistsContextMenu,this,&MainWindow::showPlaylistContextMenu);

}

void MainWindow::playTrack(QString id, QString previewUrl)
{
    ui->browser->load(QUrl(previewUrl));
}

void MainWindow::activatePlaylistActions(QString name){
    PlaylistItem* item = ui->playlistsArea->addPlaylist(name);
    connect(item,&PlaylistItem::released,this,&MainWindow::showPlaylistTracks);
}

void MainWindow::showPlaylistContextMenu(SearchResultWidget* resultWidget){
    QStringList playlists = controller->getPlaylistsNames();
    QMenu* menu = new QMenu();

    for(QString name : playlists)
    {
        QAction* action = menu->addAction(name);
        connect(action,&QAction::triggered, resultWidget, &SearchResultWidget::playlistSelected);
    }


    menu->setStyleSheet("color: rgb(211, 215, 207); background-color: rgb(40,40,40)");
    resultWidget->showPlaylistContextMenu(menu);

    QString playlist = resultWidget->getPlaylistName();
    QString trackId = resultWidget->getId();
    QString trackName = resultWidget->getName();
    QStringList artists = resultWidget->getArtists();
    QString previewUrl = resultWidget->getPreviewUrl();
    controller->addSongToUserPlaylist(playlist,trackId,trackName,artists,previewUrl);
}

void MainWindow::showPlaylistTracks(){
    PlaylistItem* item = dynamic_cast<PlaylistItem*>(sender());
    if(item)
    {
        ui->searchResultsArea->hide();
        ui->playlistTracksArea->show();
        ui->playlistTracksArea->clearTracks();
        QString status = "exibindo playlist " +item->text();
        ui->statusLabel->setText(status);
        ui->statusLabel->show();
        QString playlistName = item->text();

        QList<PlaylistTrackWidget*>* widgets = controller->configurePlaylistTrackWidget(playlistName);
        for(PlaylistTrackWidget* widget: *widgets){
            ui->playlistTracksArea->addPlaylistTrackWidget(widget);
            connect(widget,&PlaylistTrackWidget::playTrack,this,&MainWindow::playTrack);
            connect(widget,&PlaylistTrackWidget::requestTrackRemoval,controller,&Controller::removeTrackFromPlaylist);
        }

        delete widgets;
    }

}
