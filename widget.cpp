#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    quickTable.SetView(ui->tableView);

    connect(&quickTable, &QModelTable::GetData, this,
        [=](int x, int y, QString& Data)
        {
            Data.sprintf("Столбец %i, строка %i", x, y);
        }
    );

    connect(&quickTable, &QModelTable::GetCaption, this,
        [=](int x, QString& Data)
        {
            Data.sprintf("Заголовок %i", x);
        }
    );

    quickTable.SetDefaultRowHeight(16);
    quickTable.SetXCnt(4);
    quickTable.SetYCnt(2000000);

    for(int i = 0; i < 4; i++)
    {
        quickTable.SetColumnWidth(i, 180);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    quickTable.SetYCnt(quickTable.YCnt() + 1);
    quickTable.Refresh();
    ui->tableView->scrollToBottom();
}

