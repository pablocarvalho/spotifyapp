#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include <QWidget>
#include <QMenu>
namespace Ui {
class SearchResultWidget;
}

class SearchResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchResultWidget(QString name, QStringList artists, QString id, QString previewUrl, QWidget *parent = nullptr);
    ~SearchResultWidget();

    void showPlaylistContextMenu(QMenu*);

    QString getName();
    QStringList getArtists();
    QString getId();
    QString getPreviewUrl();
    QString getPlaylistName();

private:
    Ui::SearchResultWidget *ui;

    QString name;
    QStringList artists;
    QString id;
    QString previewUrl;

    QString playlistName; //Variable used for reference when a Track is about to be added in a playlist.

signals:
    void playTrack(QString id,QString previewUrl);
    void requestPlaylistsContextMenu(SearchResultWidget*);

public slots:
    void playlistSelected();
};

#endif // SEARCHRESULTWIDGET_H
