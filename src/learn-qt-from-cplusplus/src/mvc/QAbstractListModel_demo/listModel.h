#ifndef LISTMODEL_H
#define LISSTMODEL_H
#include <QAbstractListModel>

class ListModel : public QAbstractListModel {
    Q_OBJECT
public:
    ListModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex & index) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role);
private:
	enum { N=10 };
	int numbers[N];
}; 

#endif