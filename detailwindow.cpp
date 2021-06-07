#include "detailwindow.h"
#include "ui_detailwindow.h"
#include "recipe.h"
#include <QString>
#include <QDesktopServices>
#include <QUrl>

DetailWindow::DetailWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailWindow)
{
    ui->setupUi(this);
}

void DetailWindow::setRecipeDetail(int number, Recipe recipe)
{
    ui->label->setText(QString::fromStdString(recipe.name));
    ui->textEdit_3->setText(QString::fromStdString(recipe.proportions));
    ui->textEdit->setText(QString::fromStdString(recipe.directions));
    ui->lineEdit_2->setText(QString::fromStdString(recipe.link));
}

DetailWindow::~DetailWindow()
{
    delete ui;
}

void DetailWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("http://"+ui->lineEdit_2->text()));
}
