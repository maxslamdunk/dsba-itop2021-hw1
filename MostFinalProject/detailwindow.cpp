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

void DetailWindow::setRecipeDetail(int number, Recipe recipe, QList<QString> theFridge)
{
    ui->label->setText(QString::fromStdString(recipe.name));
    ui->textEdit_3->setText(QString::fromStdString(recipe.proportions));
    ui->textEdit->setText(QString::fromStdString(recipe.directions));
    ui->lineEdit_2->setText(QString::fromStdString(recipe.link));
    QList<QString> ingList = QString::fromStdString(recipe.ingredients).split(',');
    QString uHave;
    QVector<QString> theFridgeV = theFridge.toVector();
    for (int i = 0; i < theFridgeV.size(); i++)
    {
        uHave += theFridgeV[i];
        if (i != theFridgeV.size() - 1)
            uHave += ',';
    }
    QString uDont;
    QVector<QString> uDontL;
    for (int i = 0; i < ingList.size(); i++)
    {
        bool ret = true;
        if (theFridgeV.indexOf(ingList[i]) != -1)
        {
            ret = false;
        }
        else
        {
            for (int j = 0; j < theFridgeV.size();j++)
            {
                if (ingList[i].contains(theFridgeV[j]))
                {
                    ret = false;
                    break;
                }
            }
        }
        if (ret)
            uDontL.push_back(ingList[i]);
    }
    for (int i = 0; i < uDontL.size(); i++)
    {
        uDont += uDontL[i];
        if (i != uDontL.size() - 1)
        {
            uDont += ',';
        }
    }
    ui->textEdit_2->setText(uHave);
    ui->textEdit_4->setText(uDont);
    std::cout << theFridge.size()<<"list"<<std::endl;
    std::cout << theFridgeV.size()<<"vect"<<std::endl;
}

DetailWindow::~DetailWindow()
{
    delete ui;
}

void DetailWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("http://"+ui->lineEdit_2->text()));
}
