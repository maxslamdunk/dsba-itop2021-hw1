#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QDialog>
#include "recipe.h"

namespace Ui
{
    class DetailWindow;
}

class DetailWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DetailWindow(QWidget *parent = nullptr);

    ~DetailWindow();

    void setRecipeDetail(int number, Recipe recipe);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DetailWindow *ui;

    Recipe recipeDetail;
};

#endif // DETAILWINDOW_H
