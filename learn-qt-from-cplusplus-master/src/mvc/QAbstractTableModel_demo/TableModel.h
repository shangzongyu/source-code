#ifndef LISTMODEL_H
#define LISSTMODEL_H
#include <QAbstractListModel>

class TableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    TableModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
	int columnCount(const QModelIndex & parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex & index) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role);
private:
	enum { ROW_NUM=3, COL_NUM=4 };
	int numbers[ROW_NUM][COL_NUM];
}; 

#endif