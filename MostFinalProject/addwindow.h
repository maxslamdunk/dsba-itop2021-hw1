#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "recipe.h"

namespace Ui
{
    class AddWindow;
}

class AddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWindow(QWidget *parent = nullptr);
    ~AddWindow();
    void setModelPointer(QStandardItemModel* pointerToModel);
    void setDataPointer(RecipeData* recipeData);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddWindow *ui;
    QStandardItemModel* pointerToModel;
    RecipeData* pointerToRecipeData;
};

#endif // ADDWINDOW_H
