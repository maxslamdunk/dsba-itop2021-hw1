#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <QStringList>
#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QFile>
#include <QMainWindow>


struct Recipe
{
    std::string name;
    std::string proportions;
    std::string directions;
    std::string link;
    std::string ingredients;
};

class RecipeData : public QObject
{
    Q_OBJECT

    public:
        RecipeData(QStandardItemModel* model)
        {
            pointerToModel = model;
            initModel();
        }

        void save(QMainWindow* window)
        {
            QString filename = QFileDialog::getSaveFileName(window, "Save file", "", ".csv");
            QFile f(filename);
            f.open(QIODevice::WriteOnly);
            f.write("name,propotions,derictions,link,ingredients\n");
            for(int i = 0; i < (int) _data.size(); i++)
            {
                std::stringstream ss;
                ss << _data[i].name << ";" << _data[i].proportions << ";" << _data[i].directions
                   << ";" << _data[i].link << ";" << _data[i].ingredients << "\n";
                f.write(ss.str().c_str());
            }
            f.close();
        }

       Recipe getRecipe(int i)
        {
            return _data[i];
        }

        void setFields(std::string proportions, std::string directions, std::string link, int i)
        {
            _data[i].proportions = proportions;
            _data[i].directions = directions;
            _data[i].link = link;
        }

        void initModel()
        {
            for(int row = 0; row < _data.size(); row++)
            {
                int r = pointerToModel->rowCount();

                pointerToModel->insertRows(r, 1);
                for(int col = 0; col < 2; col++)
                {
                    QModelIndex index = pointerToModel->index(row, col, QModelIndex());
                    QString cellValue;
                    switch(col)
                    {
                        case 0: cellValue = QString::fromStdString(_data[row].name);
                                break;

                        case 1: cellValue = QString::fromStdString(_data[row].ingredients);
                                break;
                    }
                    pointerToModel->setData(index, cellValue);
                }
            }
        }

        void update()
        {
            for(int row = 0; row < pointerToModel->rowCount(); row++){

                if(row >= (int) _data.size())
                    _data.push_back(Recipe());

                for(int col = 0; col < pointerToModel->columnCount(); col++)
                {
                    QModelIndex index = pointerToModel->index(row,col);
                    std::string cellValue = (index.data().toString()).toStdString();

                    switch(col)
                    {
                        case 0: _data[row].name = cellValue;
                                break;

                        case 1: _data[row].ingredients = cellValue;
                                break;
                    }
                }
            }
        }

        void open(QMainWindow* window)
        {
            QString fileName = QFileDialog::getOpenFileName(window,"Open File","*.csv");
            QFile file(fileName);
            file.open(QIODevice::ReadOnly);
            file.readLine();
            while(!file.atEnd())
            {
                QByteArray line = file.readLine();
                QList<QByteArray> lineAsVector = line.split(';');
                int row = pointerToModel->rowCount();
                pointerToModel->insertRows(row, 1);
                QModelIndex index = pointerToModel->index(row, 0, QModelIndex());
                pointerToModel->setData(index,lineAsVector.at(1));
                index = pointerToModel->index(row, 1, QModelIndex());
                pointerToModel->setData(index,lineAsVector.at(5));
                std::string proportions = lineAsVector.at(2).toStdString();
                std::string directions = lineAsVector.at(3).toStdString();
                std::string link = lineAsVector.at(4).toStdString();
                _data[row].proportions = proportions;
                _data[row].directions = directions;
                _data[row].link = link;
            }
        }

    private:
        std::vector<Recipe> _data;

        QStandardItemModel* pointerToModel;

        QMainWindow* window;
};

#endif // RECIPE_H
