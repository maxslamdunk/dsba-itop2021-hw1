#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QRegularExpression>
#include <recipe.h>
#include <addwindow.h>
#include <detailwindow.h>
#include <secondwindow.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menuBar()->setNativeMenuBar(false);
    model = new QStandardItemModel(0, 2, this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ingridients"));
    recipeData = new RecipeData(model);
    proxyModel = new MyProxyModel();
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);
    QObject::connect(model, &QStringListModel::dataChanged, recipeData, &RecipeData::update);
    QObject::connect(model, &QStringListModel::rowsRemoved, recipeData, &RecipeData::update);
}

MainWindow::~MainWindow()
{
    delete recipeData;
    delete model;
    delete ui;
    delete proxyModel;
}

void MainWindow::on_pushButton_2_clicked()
{
    recipeData->open(this);
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (!ui->lineEdit->text().isEmpty())
    {
    ui->listWidget->addItem(ui->lineEdit->text());

    QList<QString> texts;
    QList<QListWidgetItem *> items =
          ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    foreach(QListWidgetItem *item, items)
      texts.append(item->text());

    proxyModel->setFilterIngredients(texts);
    ui->lineEdit->clear();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());

    QList<QString> texts;
    QList<QListWidgetItem *> items =
          ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    foreach(QListWidgetItem *item, items)
      texts.append(item->text());

    proxyModel->setFilterIngredients(texts);
}

void MainWindow::on_pushButton_5_clicked()
{
    AddWindow addWindow;
    addWindow.setModelPointer(model);
    addWindow.setDataPointer(recipeData);
    addWindow.setModal(true);
    addWindow.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    QModelIndex proxyIndex = ui->tableView->currentIndex();
    QModelIndex modelIndex = proxyModel->mapToSource(proxyIndex);
    int selectedRow = modelIndex.row();

    QList<QString> texts;
    QList<QListWidgetItem *> items =
          ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    foreach(QListWidgetItem *item, items)
      texts.append(item->text());

    DetailWindow detailWindow;
    Recipe recipe = recipeData->getRecipe(selectedRow);
    detailWindow.setRecipeDetail(selectedRow, recipe, texts);
    detailWindow.setModal(true);
    detailWindow.exec();
}

void MainWindow::on_pushButton_7_clicked()
{
    QModelIndex proxyIndex = ui->tableView->currentIndex();
    QModelIndex modelIndex = proxyModel->mapToSource(proxyIndex);
    int selectedRow = modelIndex.row();
    model->removeRows(selectedRow, 1);
    if (int rows = proxyModel->rowCount() == 0)
    {
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    recipeData->save(this);
}

void MainWindow::on_actionAbout_triggered()
{
     SecondWindow secondWindow;
     secondWindow.setModal(true);
     secondWindow.exec();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    int rows = proxyModel->rowCount();
    if (rows != 0)
    {
    quint32 row = QRandomGenerator::global()->bounded(0, rows);
    QModelIndex proxyIndex = proxyModel->index(row, 0);
    QModelIndex modelIndex = proxyModel->mapToSource(proxyIndex);
    int selectedRow = modelIndex.row();
    DetailWindow detailWindow;
    Recipe recipe = recipeData->getRecipe(selectedRow);

    QList<QString> texts;
    QList<QListWidgetItem *> items =
          ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    foreach(QListWidgetItem *item, items)
      texts.append(item->text());

    detailWindow.setRecipeDetail(selectedRow, recipe, texts);
    detailWindow.setModal(true);
    detailWindow.exec();
    }
}
