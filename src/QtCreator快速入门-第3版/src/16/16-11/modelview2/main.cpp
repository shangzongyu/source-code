#include <QApplication>
#include <QDebug>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QListWidget listWidget;
    // 一种添加项目的简便方法
    new QListWidgetItem("a", &listWidget);

    // 添加项目的另一种方法，这样还可以进行各种设置
    QListWidgetItem *listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText("b");
    listWidgetItem->setIcon(QIcon("../modelview2/yafeilinux.png"));
    listWidgetItem->setToolTip("this is b!");
    listWidget.insertItem(1, listWidgetItem);

    // 设置排序为倒序
    listWidget.sortItems(Qt::DescendingOrder);

    // 显示列表部件
    listWidget.show();

    QTreeWidget treeWidget;

    // 必须设置列数
    treeWidget.setColumnCount(2);

    // 设置标头
    QStringList headers;
    headers << "name" << "year";
    treeWidget.setHeaderLabels(headers);

    // 添加项目
    QTreeWidgetItem *grade1 = new QTreeWidgetItem(&treeWidget);
    grade1->setText(0, "Grade1");
    QTreeWidgetItem *student = new QTreeWidgetItem(grade1);
    student->setText(0, "Tom");
    student->setText(1, "1986");
    QTreeWidgetItem *grade2 = new QTreeWidgetItem(&treeWidget, grade1);
    grade2->setText(0, "Grade2");
    treeWidget.show();


    // 创建表格部件，同时指定行数和列数
    QTableWidget tableWidget(3, 2);

    // 创建表格项目，并插入到指定单元
    QTableWidgetItem *tableWidgetItem = new QTableWidgetItem("qt");
    tableWidget.setItem(1, 1, tableWidgetItem);

    // 创建表格项目，并将它们作为标头
    QTableWidgetItem *headerV = new QTableWidgetItem("first");
    tableWidget.setVerticalHeaderItem(0, headerV);
    QTableWidgetItem *headerH = new QTableWidgetItem("ID");
    tableWidget.setHorizontalHeaderItem(0, headerH);
    tableWidget.show();

    // 设置选择模式为单选
    listWidget.setSelectionMode(QAbstractItemView::SingleSelection);
    // 启用拖动
    listWidget.setDragEnabled(true);
    // 设置接受拖放
    listWidget.viewport()->setAcceptDrops(true);
    // 设置显示将要被放置的位置
    listWidget.setDropIndicatorShown(true);
    // 设置拖放模式为移动项目，如果不设置，默认为复制项目
    listWidget.setDragDropMode(QAbstractItemView::InternalMove);


    return app.exec();
}

