#include "threadtablemodel.h"

ThreadTableModel::ThreadTableModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QModelIndex ThreadTableModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex ThreadTableModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ThreadTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

int ThreadTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}

QVariant ThreadTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
    return QVariant();
}
