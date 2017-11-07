#include <QApplication>
#include <QtWidgets>
#include "progress.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Progress progress;
    progress.show();

    return a.exec();
}
