#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget wgt;

    QPixmap img_one(":/wraxius"),img(":/demon"), cursor(":/cursor");
    QCursor cursor_c(cursor);

    QWidget *pwt1 = new QWidget(&wgt);
    QPalette pall;
    QWidget *pwt2 = new QWidget(&wgt);
    QPalette pall2;

    pall.setBrush(pwt1->backgroundRole(),QBrush(img_one));
    pwt1->setPalette(pall);
    pwt1->resize(img_one.width(),img_one.height());
    pwt1->move(500,0);
    pwt1->setAutoFillBackground(true);
    pall2.setBrush(pwt2->backgroundRole(),QBrush(img));
    pwt2->setPalette(pall2);
    pwt2->resize(img.width(),img.height());
    pwt2->move(50,45);
    pwt2->setAutoFillBackground(true);
    wgt.setCursor(cursor_c);
    wgt.resize(1250,400);

    QWidget *widg = new QWidget(&wgt);
    QScrollArea scroll_a;
    QPixmap backgroundFon(":/brick");
    QPalette pall_background;
    pall_background.setBrush(widg->backgroundRole(),QBrush(backgroundFon));
    widg->setPalette(pall_background);
    widg->setAutoFillBackground(true);
    widg->setFixedSize(backgroundFon.width(),backgroundFon.height());
    widg->setCursor(cursor_c);// but you cant see monsters because when you created backgroundFon it hide previous image

    scroll_a.setWidget(widg);
    scroll_a.resize(700,550);
    scroll_a.show();


    return a.exec();
}
