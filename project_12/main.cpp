#include <QtWidgets>
#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QWidget *p_wgt = new QWidget;
//    QStringListModel model_one;
//    model_one.setStringList(QStringList() << "tomko" << "bomko" << "barabas");

//    QTreeView *p_tree_v = new QTreeView;
//    p_tree_v->setModel(&model_one);

//    QListView *p_list_v = new QListView;
//    p_list_v->setModel(&model_one);

//    QTableView *p_table_v = new QTableView;
//    p_table_v->setModel(&model_one);

//    QItemSelectionModel p_selection(&model_one);
//    p_tree_v->setSelectionModel(&p_selection);
//    p_list_v->setSelectionModel(&p_selection);
//    p_table_v->setSelectionModel(&p_selection);

//    QHBoxLayout *p_hbL = new QHBoxLayout;
//    p_hbL->addWidget(p_tree_v);
//    p_hbL->addWidget(p_list_v);
//    p_hbL->addWidget(p_table_v);

//    p_wgt->setLayout(p_hbL);
//    p_wgt->show();

//    return a.exec();
//}

#include "simple_delegate.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    QStringListModel model;
//    model.setStringList(QStringList() << "item1" << "item2" << "item3");

//    QTableView list_view;
//    list_view.setModel(&model);
//    list_view.setItemDelegate(new SimpleDelegate(&list_view));
//    list_view.viewport()->setAttribute(Qt::WA_Hover);
//    list_view.show();

//    return a.exec();
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableWidget tableWidget(3, 3);

    tableWidget.setItemDelegate(new SimpleDelegate(&tableWidget));
    tableWidget.viewport()->setAttribute(Qt::WA_Hover);

    for(int row=0; row!=tableWidget.rowCount(); ++row){
        for(int column=0; column!=tableWidget.columnCount(); ++column) {

            QTableWidgetItem *newItem = new QTableWidgetItem(QString("%1").arg((row+1)*(column+1)));
            tableWidget.setItem(row, column, newItem);
        }
    }

    tableWidget.resize(450,450);
    tableWidget.show();

    return a.exec();
}
