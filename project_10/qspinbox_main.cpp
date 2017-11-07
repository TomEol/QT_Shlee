#include <QtWidgets>

int main(int argc,char **argv){
    QApplication a(argc,argv);
    QSpinBox spb;

    spb.setRange(1,100);
    spb.setSuffix(" MB");
    spb.setButtonSymbols(QSpinBox::PlusMinus);
    spb.setWrapping(true);
    spb.show();
    spb.resize(100,30);

    QDateTimeEdit *someTime = new QDateTimeEdit(QDateTime::currentDateTime());
    someTime->show();
    someTime->move(500,500);
    someTime->resize(100,100);

    return a.exec();
}
