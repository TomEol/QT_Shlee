#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel labe("hello my first qt project =)");
    labe.show();

    return a.exec();
}
