#ifndef SEARCHAREAWIDGET_H
#define SEARCHAREAWIDGET_H

#include <QWidget>

namespace Ui {
class SearchAreaWidget;
}

class SearchAreaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchAreaWidget(QWidget *parent = nullptr);
    ~SearchAreaWidget();

private:
    Ui::SearchAreaWidget *ui;
};

#endif // SEARCHAREAWIDGET_H
