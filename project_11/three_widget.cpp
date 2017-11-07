#include <QtWidgets>

int main(int argc,char **argv){
    QApplication app(argc,argv);

    QTreeWidget tree_widget;
    QStringList str_tree_wg;

    str_tree_wg << "Folders" << "Used space";
    tree_widget.setHeaderLabels(str_tree_wg);
    tree_widget.setSortingEnabled(true);
    tree_widget.setSelectionMode(QAbstractItemView::MultiSelection);

    QTreeWidgetItem *p_widget_tree_Item = new QTreeWidgetItem(&tree_widget);
    p_widget_tree_Item->setText(0,"Local Disc(C) ");
    p_widget_tree_Item->setIcon(0,QPixmap("F:/_QT/_qt/ch_11/project_11/Windows.png"));

    QTreeWidgetItem *p_widget_tree_ItemDir = 0;
    for(int i = 0 ; i < 20; ++i){
        p_widget_tree_ItemDir = new QTreeWidgetItem(p_widget_tree_Item);
        p_widget_tree_ItemDir->setText(0,"Directory" + QString::number(i));
        p_widget_tree_ItemDir->setText(1,QString::number(i) + "MB");
        p_widget_tree_ItemDir->setIcon(0,QPixmap("F:/_QT/_qt/ch_11/project_11/Linux.png"));
        p_widget_tree_ItemDir->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
    }

    tree_widget.setItemExpanded(p_widget_tree_Item,true);
    tree_widget.resize(300,300);
    tree_widget.show();


    return app.exec();
}
