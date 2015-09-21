#ifndef THREADTABLEMODEL_H
#define THREADTABLEMODEL_H

#include <QAbstractItemModel>

class ThreadTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ThreadTableModel(QObject *parent);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // THREADTABLEMODEL_H
