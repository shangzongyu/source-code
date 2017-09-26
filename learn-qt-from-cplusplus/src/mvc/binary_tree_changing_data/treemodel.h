#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QTimer>

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	TreeModel();
	int rowCount ( const QModelIndex & parent ) const;
	int columnCount ( const QModelIndex & parent ) const;
	QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
	QModelIndex parent ( const QModelIndex & index ) const;
	QVariant data ( const QModelIndex & index, int role ) const;
private slots:
	void timerHit();

private:
	enum {N=15};
	int numbers[N];
	QTimer * timer;
};

#endif // TREEMODEL_H
