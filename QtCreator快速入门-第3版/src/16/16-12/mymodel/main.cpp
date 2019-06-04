#include <QApplication>
#include "stringlistmodel.h"
#include <QListView>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStringList list;
    list << "a" << "b" << "c";
    StringListModel model(list);

    QListView listView;
    listView.setModel(&model);
    listView.show();

    QTableView tableView;
    tableView.setModel(&model);
    tableView.show();

    model.insertRows(3, 2);
    model.removeRows(0, 1);

    listView.setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView.setDragEnabled(true);
    listView.setAcceptDrops(true);
    listView.setDropIndicatorShown(true);

    return app.exec();
}
