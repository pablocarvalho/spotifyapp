#include "searchresultsarea.h"
#include "ui_searchresultsarea.h"
#include <QDebug>
SearchResultsArea::SearchResultsArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResultsArea)
{
    ui->setupUi(this);

}

SearchResultsArea::~SearchResultsArea()
{
    delete ui;    
}

void SearchResultsArea::addResult(SearchResultWidget* resultWidget)
{
    resultWidget->setParent(this);
    ui->verticalLayout->addWidget(resultWidget);
}

void SearchResultsArea::clearResults()
{

    QList<SearchResultWidget *> widgets = findChildren<SearchResultWidget *>();
    foreach(SearchResultWidget * widget, widgets)
    {
        delete widget;
    }
}
