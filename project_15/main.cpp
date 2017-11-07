#include <QtWidgets>
#include <QApplication>
#include "filterFromTom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVBoxLayout *layout_grid = new QVBoxLayout;
    QWidget *wgt = new QWidget;

    QTextEdit *text_editor = new QTextEdit;
    QPushButton *somePushB = new QPushButton("&START");


    text_editor->installEventFilter(new filterFromTom(text_editor));
    somePushB->installEventFilter(new filterFromTom(somePushB));

    layout_grid->addWidget(text_editor);
    layout_grid->addWidget(somePushB);

    wgt->setLayout(layout_grid);
    wgt->resize(500,500);
    wgt->show();


    return a.exec();
}
