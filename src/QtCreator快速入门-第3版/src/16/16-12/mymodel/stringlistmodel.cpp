#include "stringlistmodel.h"
#include <QMimeData>
#include <QDataStream>

int StringListModel::rowCount(const QModelIndex &) const
{
    return stringList.count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return stringList.at(index.row());
    else
        return QVariant();
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    // 如果该索引无效，那么只支持放入操作
    if (!index.isValid())
        return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;

    // 如果该索引有效，那么既支持拖拽操作，也支持放入操作
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable
            | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

}

bool StringListModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool StringListModel::insertRows(int position, int rows,
                                 const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        stringList.insert(position, "");
    }
    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int position, int rows,
                                 const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

// 设置支持放入动作
Qt::DropActions StringListModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

// 设置在拖放操作中导出的条目的数据的编码类型
QStringList StringListModel::mimeTypes() const
{
    QStringList types;
    // "application/vnd.text.list"是自定义的类型，在后面的函数中要保持一致
    types << "application/vnd.text.list";
    return types;
}

// 将拖放的数据放入QMimeData中
QMimeData * StringListModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }
    // 将数据放入QMimeData中
    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

// 将拖放的数据放入模型中
bool StringListModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                   int row, int column, const QModelIndex &parent)
{
    // 如果放入动作是Qt::IgnoreAction，那么返回true
    if (action == Qt::IgnoreAction)
        return true;
    // 如果数据的格式不是指定的格式，那么返回false
    if (!data->hasFormat("application/vnd.text.list"))
        return false;
    // 因为这里是列表，只用一列，所以列大于0时返回false
    if (column > 0)
        return false;
    // 设置开始插入的行
    int beginRow;
    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    // 将数据从QMimeData中读取出来，然后插入到模型中
    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;
    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;
        ++rows;
    }
    insertRows(beginRow, rows, QModelIndex());
    foreach (const QString &text, newItems) {
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, text);
        beginRow++;
    }
    return true;
}

