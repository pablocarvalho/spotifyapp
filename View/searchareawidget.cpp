#include "searchareawidget.h"
#include "ui_searchareawidget.h"

SearchAreaWidget::SearchAreaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchAreaWidget)
{
    ui->setupUi(this);
}

SearchAreaWidget::~SearchAreaWidget()
{
    delete ui;
}
