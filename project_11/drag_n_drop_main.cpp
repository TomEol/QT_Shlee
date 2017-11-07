#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList list_string;
    QListWidget list_widget;

    QListWidgetItem *p_list_widget_item = 0;

    list_widget.setIconSize(QSize(48,48));
    list_widget.setSelectionMode(QAbstractItemView::MultiSelection);
    list_widget.setViewMode(QListView::IconMode);

    list_string << "Linux" << "Windows" << "MacOSX" << "Android";

    foreach (QString str, list_string) {
       p_list_widget_item = new QListWidgetItem(str,&list_widget);
       QIcon icon(QString("F:/_QT/_qt/ch_11/project_11/" + str + ".png"));
       p_list_widget_item->setIcon(icon);
       p_list_widget_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable |
                                    Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
    }

    list_widget.resize(400,400);
    list_widget.show();

    return a.exec();
}
