#include "addwindow.h"
#include "ui_addwindow.h"
#include <QString>

AddWindow::AddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWindow)
{
    ui->setupUi(this);
}

void AddWindow::setModelPointer(QStandardItemModel* model)
{
    pointerToModel = model;
}

void AddWindow::setDataPointer(RecipeData *recipeData)
{
    pointerToRecipeData = recipeData;
}

AddWindow::~AddWindow()
{
    delete ui;
}

void AddWindow::on_pushButton_clicked()
{
    int row = pointerToModel->rowCount();
    pointerToModel->insertRows(row, 1);
    QModelIndex index = pointerToModel->index(row, 0, QModelIndex());
    pointerToModel->setData(index,ui->lineEdit->text());
    index = pointerToModel->index(row, 1, QModelIndex());
    pointerToModel->setData(index,ui->textEdit_3->toPlainText());
    std::string proportions = ui->textEdit->toPlainText().toStdString();
    std::string directions = ui->textEdit_2->toPlainText().toStdString();
    std::string link = ui->lineEdit_4->text().toStdString();
    pointerToRecipeData->setFields(proportions, directions, link, row);
}
