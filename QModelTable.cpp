#include "QModelTable.h"

QModelTable::QModelTable(QObject *parent) : QAbstractItemModel(parent)
{
    XCnt_ = 0;
    YCnt_ = 0;
    table = nullptr;
}

void QModelTable::SetDefaultRowHeight(int height)
{
    if(table)
    {
        table->verticalHeader()->setMinimumSectionSize(height);
        table->verticalHeader()->setDefaultSectionSize(height);
    }
}

void QModelTable::SetColumnWidth(int x, int width)
{
    if(table)
    {
        table->horizontalHeader()->resizeSection(x, width);
    }
}

void QModelTable::SetView(QTableView * table)
{
    table->setFocusPolicy(Qt::NoFocus);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->verticalHeader()->setVisible(false);

    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);

    table->horizontalHeader()->setMinimumSectionSize(1);

    table->setModel(this);

    this->table = table;
}

QModelIndex QModelTable::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex QModelTable::parent(const QModelIndex &index) const
{
    return QModelIndex(); // QModelIndex::QModelIndex() is empty 'invalid' model index
}

int QModelTable::rowCount(const QModelIndex &parent) const
{
    return YCnt_;
}

int QModelTable::columnCount(const QModelIndex &parent) const
{
    return XCnt_;
}

void QModelTable::SetXCnt(int XCnt)
{
    if(XCnt > XCnt_)
    {
        beginInsertColumns(QModelIndex(), XCnt_, XCnt - 1);
        XCnt_ = XCnt;
        QAbstractItemModel::endInsertColumns();
    }

    if(XCnt < XCnt_)
    {
        beginRemoveColumns(QModelIndex(), XCnt, XCnt_ - 1);
        XCnt_ = XCnt;
        QAbstractItemModel::endRemoveColumns();
    }
}

void QModelTable::SetYCnt(int YCnt)
{
    if(YCnt > YCnt_)
    {
        beginInsertRows(QModelIndex(), YCnt_, YCnt - 1);
        YCnt_ = YCnt;
        QAbstractItemModel::endInsertRows();
    }

    if(YCnt < YCnt_)
    {
        beginRemoveRows(QModelIndex(), YCnt, YCnt_ - 1);
        YCnt_ = YCnt;
        QAbstractItemModel::endRemoveRows();
    }
}

int QModelTable::XCnt()
{
    return XCnt_;
}

int QModelTable::YCnt()
{
    return YCnt_;
}

QVariant QModelTable::data(const QModelIndex &index, int role) const
{
    if((index.column() >= columnCount()) || (index.row() >= rowCount()) || (role != Qt::DisplayRole))
    {
        return QVariant(); // is empty 'invalid' QVariant
    }

    QString ret;
    emit GetData(index.column(), index.row(), ret);
    return QVariant(ret);
}

void QModelTable::Refresh()
{
    emit dataChanged(QModelIndex(), QModelIndex());
}

void QModelTable::RefreshCaption()
{
    emit headerDataChanged(Qt::Horizontal, 0, XCnt_);
}

QVariant QModelTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    QString ret;
    if((orientation == Qt::Horizontal) && (role == Qt::DisplayRole))
    {
        emit GetCaption(section, ret);
        return QVariant(ret);
    }

    return QAbstractItemModel::headerData(section,orientation, role);
}
