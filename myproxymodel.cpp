#include "myproxymodel.h"
#include <iostream>

MyProxyModel::MyProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{

    ingredients = QList<QString>();
}

bool MyProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
    QString rowRecipe = sourceModel()->data(index).toString();

    if(ingredients.isEmpty()) // if the user did not write a country
    {
        return true; // only filter by population
    }

    bool ret = true;

    for (int i = 0; i < ingredients.size(); i++)
    {
        if (rowRecipe.toStdString().find(ingredients[i].toStdString()) == std::string::npos)
        {
            ret = false;
            break;
        }
    }
    return ret;
}

void MyProxyModel::setFilterIngredients(QList<QString> ingredients)
{
    this->ingredients = ingredients.isEmpty() ? QList<QString>() : ingredients;
    invalidateFilter();
}
