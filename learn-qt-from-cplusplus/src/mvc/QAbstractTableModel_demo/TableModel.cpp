#include "TableModel.h"

TableModel::TableModel(QObject *parent) :QAbstractTableModel(parent) 
{ 
	for (int i=0;i<ROW_NUM;i++)
		for (int j=0; j<COL_NUM;j++)
			numbers[i][j] = i+j;
}
int TableModel::rowCount(const QModelIndex & /*parent*/) const 
{
   return ROW_NUM;
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const 
{
   return COL_NUM;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole) 
       return QVariant( numbers[index.row()] [index.column()] );
    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsSelectable |   Qt::ItemIsEnabled  | Qt::ItemIsEditable;
}

bool TableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role != Qt::EditRole) return true;
	numbers[index.row()] [index.column()] = value.toInt();
	return true;
}