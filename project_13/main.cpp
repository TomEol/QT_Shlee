#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSpinBox spb;
    QPalette n_pal = spb.palette();

    n_pal.setColor(QPalette::Button,Qt::Dense3Pattern);
    n_pal.setColor(QPalette::ButtonText,Qt::blue);
    n_pal.setColor(QPalette::Text,Qt::darkBlue);
    n_pal.setColor(QPalette::Active, QPalette::Base,Qt::lightGray);

    spb.setPalette(n_pal);
    spb.resize(200,200);
    spb.show();

    //a.setStyle(new QWindowsStyle);
    QPalette pal(Qt::yellow,Qt::blue);
    a.setPalette(pal);

    QSpinBox two;
    two.setPalette(pal);

    two.resize(300,300);
    two.show();

    return a.exec();
}
