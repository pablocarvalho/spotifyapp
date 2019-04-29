#ifndef SEARCHRESULTSAREA_H
#define SEARCHRESULTSAREA_H

#include <QWidget>
#include "searchresultwidget.h"
#include <QMenu>

namespace Ui {
class SearchResultsArea;
}

class SearchResultsArea : public QWidget
{
    Q_OBJECT

public:
    explicit SearchResultsArea(QWidget *parent = nullptr);
    ~SearchResultsArea();

    void clearResults();
    void addResult(SearchResultWidget* resultWidget);

private:
    Ui::SearchResultsArea *ui;
};

#endif // SEARCHRESULTSAREA_H
