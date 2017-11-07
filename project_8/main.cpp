#include <QApplication>
#include "button.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Button button;
    button.show();

    return a.exec();
}
