#ifndef NEWPLAYLISTDIALOG_H
#define NEWPLAYLISTDIALOG_H

#include <QDialog>

namespace Ui {
class NewPlaylistDialog;
}

class NewPlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPlaylistDialog(QWidget *parent = nullptr);
    ~NewPlaylistDialog();

    QString getNewPlaylistName();

private:
    Ui::NewPlaylistDialog *ui;
};

#endif // NEWPLAYLISTDIALOG_H
