#include <QtWidgets>

int main(int argc,char **argv){
    QApplication app(argc,argv);

    QComboBox com_box;
    QStringList string_list;

    string_list << "Tom1" << "Tom2" << "Tom3";
    com_box.addItems(string_list);
    com_box.setEditable(true);
    com_box.show();

    QStringList list_string;
    QTabWidget  tab;

    list_string << "Linux" << "Windows" << "MacOSX" << "Android";
    foreach(QString str,list_string){
        tab.addTab(new QLabel(str,&tab),QPixmap("F:/_QT/_qt/ch_11/project_11/Android.png"),str);
    }
    tab.resize(500,500);
    tab.show();

    QToolBox tool_box;
    QStringList list_string2;

    list_string2 << "Linux" << "Windows" << "MacOSX" << "Android";
    foreach(QString str, list_string2){
        tool_box.addItem(new QLabel(str,&tool_box),QPixmap("F:/_QT/_qt/ch_11/project_11/"+str),str);
    }
    tool_box.resize(100,80);
    tool_box.show();

    return app.exec();
}
