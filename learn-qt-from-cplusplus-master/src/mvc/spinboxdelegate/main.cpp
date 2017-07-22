
/* This file is part of the examples of the Qt Toolkit.*/

#include <QApplication>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QTableView>

#include "delegate.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	/* QApplication::setStyle("plastique"); */

    QStandardItemModel model(4, 2);
    QTableView tableView;
    tableView.setModel(&model);

    SpinBoxDelegate spinbox_dg;
    tableView.setItemDelegate(&spinbox_dg);

    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 2; ++column) {
            QModelIndex index = model.index(row, column, QModelIndex());
            model.setData(index, QVariant((row+1) * (column+1)));
        }
    }
    tableView.setWindowTitle(QObject::tr("Spin Box Delegate"));
    tableView.show();
    return app.exec();
}

