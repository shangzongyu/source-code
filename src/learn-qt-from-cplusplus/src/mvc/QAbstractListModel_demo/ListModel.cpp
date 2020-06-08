#include "ListModel.h"

ListModel::ListModel(QObject *parent) :QAbstractListModel(parent) 
{ 
	for (int i=0;i<N;i++)
		numbers[i] = i;
}
int ListModel::rowCount(const QModelIndex & /*parent*/) const 
{
   return N;
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole) {
		int idx = index.row();
       return QVariant( numbers[idx] );
	}
    return QVariant();
}

Qt::ItemFlags ListModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsSelectable |   Qt::ItemIsEnabled  | Qt::ItemIsEditable;
}

bool ListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role != Qt::EditRole) return true;
	int idx = index.row();
	numbers[idx] = value.toInt();
	return true;
}