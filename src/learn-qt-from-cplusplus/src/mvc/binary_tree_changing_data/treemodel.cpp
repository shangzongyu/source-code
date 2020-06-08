#include "treemodel.h"

TreeModel::TreeModel()
{
	int values[N]={36,10,26,3,7, 11,15, 1,2,3,4,5,6,7,8};
	for (int i=0; i<N; i++)
		numbers[i] = values[i];
	
	timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()) , this, SLOT(timerHit()));
    timer->start();
}

void TreeModel::timerHit()
{
	numbers[14] = ( numbers[14] + 1 ) % 60;
	numbers[6] = numbers[14]+ numbers[13];
	numbers[2] = numbers[6] + numbers[5];
	numbers[0] = numbers[2] + numbers[1];

	QModelIndex idx_14 = createIndex(1,0,14);
	QModelIndex idx_6  = createIndex(1,0,6);
	QModelIndex idx_2  = createIndex(1,0,2);
	QModelIndex idx_0  = createIndex(0,0,0);
	
	emit dataChanged(idx_14, idx_14);
	emit dataChanged(idx_6,  idx_6 );
	emit dataChanged(idx_2,  idx_2 );
	emit dataChanged(idx_0,  idx_0 );
}

int TreeModel::rowCount ( const QModelIndex & parent ) const
{
	if ( ! parent.isValid() )
		return 1;
	if (parent.internalId() < N/2 )
		return 2;
	return 0;
}

int TreeModel::columnCount ( const QModelIndex & parent ) const 
{
	return 1;
}

QModelIndex TreeModel::index ( int row, int column, const QModelIndex & parent ) const 
{
	if ( ! parent.isValid() )
		return createIndex(row, column, 0);

	int parent_idx = parent.internalId();
	int idx = parent_idx * 2 + ( row + 1 );
	return createIndex(row, column, idx );
}

QModelIndex TreeModel::parent ( const QModelIndex & index ) const
{
	if (index.internalId() == 0) 
		return QModelIndex();
	
	int parent_idx = (index.internalId() - 1 )/2;
	return createIndex( (parent_idx+1) % 2, 0, parent_idx );
}

QVariant TreeModel::data ( const QModelIndex & index, int role  ) const 
{
	switch (role) {
	case Qt::DisplayRole:
		int value = numbers[ index.internalId() ];
		return QVariant( value );
	}
	return QVariant();
}