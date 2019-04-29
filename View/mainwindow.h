#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controller.h>
#include "searchresultwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Controller* controller;

    QMenu* playlistMenu;    

private slots:
    void customizeInterface();
    void searchSongRequest();
    void addSearchResult(QString name, QStringList artist, QString id, QString previewUrl);
    void playTrack(QString id, QString previewUrl);
    void activatePlaylistActions(QString);
    void showPlaylistContextMenu(SearchResultWidget*);
    void showPlaylistTracks();    

};

#endif // MAINWINDOW_H
