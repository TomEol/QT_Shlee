#include <QtWidgets>
#include <QApplication>


//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    QLineEdit txt("enter text here:");
//    txt.show();
//    txt.resize(300,300);

//    for(int i = 0 ; i < Qt::Key_Z - Qt::Key_A;++i){
//        QChar ch = 65 + i;
//        int nKey = Qt::Key_A + i;

//        QKeyEvent key_press(QEvent::KeyPress,nKey,Qt::NoModifier,ch);
//        QApplication::sendEvent(&txt,&key_press);

//        QKeyEvent key_release(QEvent::KeyRelease,nKey,Qt::NoModifier,ch);
//        QApplication::sendEvent(&txt,&key_release);
//    }

//    return a.exec();
//}

#include "keyfilter.h";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLineEdit txt;
    txt.show();

    keyFilter *pFilter = new keyFilter(&txt);
    txt.installEventFilter(pFilter);


    return a.exec();
}
