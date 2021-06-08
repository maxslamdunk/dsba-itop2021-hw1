#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H
#include <QSortFilterProxyModel>

class MyProxyModel : public QSortFilterProxyModel
{
    public:
        MyProxyModel(QObject* parent = 0);

        void setFilterIngredients(QList<QString> ingredients);

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

    private:
        QList<QString> ingredients;
};

#endif // MYPROXYMODEL_H
