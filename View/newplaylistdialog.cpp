#include "newplaylistdialog.h"
#include "ui_newplaylistdialog.h"

NewPlaylistDialog::NewPlaylistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPlaylistDialog)
{
    ui->setupUi(this);
}

NewPlaylistDialog::~NewPlaylistDialog()
{
    delete ui;
}

QString NewPlaylistDialog::getNewPlaylistName(){
    return ui->lineEdit->text();
}
