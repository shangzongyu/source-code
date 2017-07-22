#include "revertProxyModel.h"
#include "revertProxyModel.h"
#include <QFile>
#include <QTextStream>

#define DEBUG
#ifdef DEBUG
static QFile file("log.txt");
static QTextStream stream ( & file );
#endif

RevertProxyModel::RevertProxyModel(QObject * parent ):
	QAbstractProxyModel( parent )
{
	vector.clear();
	#ifdef DEBUG
	file.open( QIODevice::WriteOnly | QIODevice::Text );
	#endif
}

QModelIndex	RevertProxyModel::mapToSource ( const QModelIndex & proxy_index ) const
{
    if (!proxy_index.isValid())
        return QModelIndex();
	int pos = proxy_index.internalId();

	#ifdef DEBUG
	if (pos >= vector.size() )
		stream << " error in mapToSource: out of vector range" << endl;
	#endif	

	return vector[ pos ];
}

int RevertProxyModel::register_index(const QModelIndex & source_index) const
{
	int pos = vector.indexOf( source_index );
	if ( pos == -1 ){
		vector.push_back( source_index );
		pos = vector.size() - 1;
	}
	return pos;
}


QModelIndex	RevertProxyModel::mapFromSource ( const QModelIndex & source_index ) const
{
    if (!source_index.isValid())
        return QModelIndex();
	int rowCount = sourceModel()->rowCount( source_index );
	
	int pos = register_index( source_index );
	return createIndex( rowCount -1 - source_index.row(),
					source_index.column(),  pos );
}

QModelIndex RevertProxyModel::index(int row, int column, const QModelIndex & proxy_parent) const
{
	QModelIndex source_parent = mapToSource( proxy_parent );
	int rowCount = sourceModel()->rowCount( source_parent );
	QModelIndex source_index = sourceModel()->index( rowCount - 1 - row, 
										column, source_parent );
	int pos = register_index( source_index );

	#ifdef DEBUG
	stream << "::index(" << row << "," << column << ",proxy_parent{" 
		   << proxy_parent.row() << "," << proxy_parent.column() << ","
		   << proxy_parent.internalId() << "} )" <<endl;
	stream << "  source: [" << source_index.data().toString() << "], "
		   << "registered at " << pos << endl;
	#endif

	return createIndex( row, column, pos );
}

QModelIndex RevertProxyModel::parent(const QModelIndex & proxy_child) const
{
	QModelIndex source_child  = mapToSource( proxy_child );
	QModelIndex source_parent = sourceModel()->parent( source_child );

	#ifdef DEBUG
	stream << endl;
	stream << "::parent( proxy_child { " << proxy_child.row() << "," 
		<< proxy_child.column() << "," << proxy_child.internalId() 
		<< " } )" << endl;
	stream << "    source_child: [" << source_child.data().toString() 
		   << "] ==> source_parent [" << source_parent.data().toString() << "]" <<  endl;
	#endif

	return mapFromSource( source_parent );
}

int RevertProxyModel::rowCount(const QModelIndex & proxy_parent) const
{
	QModelIndex source_parent = mapToSource(proxy_parent);
	int rowCount = sourceModel()->rowCount( source_parent );

	#ifdef DEBUG
	stream << "::rowCount( proxy_parent{" << proxy_parent.row() << "," 
		   << proxy_parent.column() << "," << proxy_parent.internalId()
		   << "} )" << endl;
	stream << "  source_parent: [" << source_parent.data().toString() 
		   << "]  rowCount = " << rowCount << endl;
	#endif

	return rowCount;
}

int RevertProxyModel::columnCount(const QModelIndex & proxy_parent) const
{
	QModelIndex source_parent = mapToSource(proxy_parent);
	return sourceModel()->columnCount( source_parent );
}


