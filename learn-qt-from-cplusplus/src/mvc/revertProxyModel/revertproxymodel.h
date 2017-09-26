#ifndef REVERT_PROXY_MODEL_H
#define REVERT_PROXY_MODEL_H
#include <QAbstractProxyModel>
#include <QVector>

class RevertProxyModel: public QAbstractProxyModel
{
	Q_OBJECT
public:
	RevertProxyModel(QObject * parent=0 );

	QModelIndex	mapToSource ( const QModelIndex & proxy_index ) const;
	QModelIndex	mapFromSource ( const QModelIndex & source_index ) const;

	QModelIndex index(int row, int column, const QModelIndex & proxy_parent) const;
	QModelIndex parent(const QModelIndex & proxy_child) const;
	int rowCount(const QModelIndex & proxy_parent) const;
	int columnCount(const QModelIndex & proxy_parent) const;

private:
	int register_index(const QModelIndex & source_index) const;

	mutable QVector<QModelIndex> vector;
};

#endif 


