#ifndef QMODELTABLE_H
#define QMODELTABLE_H

#include <QtWidgets>

class QModelTable : public QAbstractItemModel
{
    Q_OBJECT

public:
    QModelTable(QObject *parent = Q_NULLPTR);

    void SetView(QTableView * table);
    void SetXCnt(int XCnt);
    void SetYCnt(int YCnt);

    void Refresh();
    void RefreshCaption();

    void SetDefaultRowHeight(int height);
    void SetColumnWidth(int x, int width);

    int XCnt();
    int YCnt();

private:
    int XCnt_, YCnt_;
    QTableView * table;

    // обязательные виртуальные функции при сабклассировании
    // QAbstractTableModel 'must be' implementations
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    // QAbstractItemModel 'must be' implementations
    //Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:
    void GetData(int x, int y, QString& Data) const;
    void GetCaption(int x, QString& Data) const;
};

#endif
