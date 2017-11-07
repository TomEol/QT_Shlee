#include "brightanddark.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   QLabel l;
   l.resize(800,800);

   QPixmap pi(l.size());
   QPainter p;
   p.begin(&pi);

   p.drawPixmap(l.rect(),QPixmap(":/2.jpg"));
   p.end(); // Don't forget this line!


   QBitmap bmp(l.size());
   bmp.fill();

   p.begin(&bmp);
   p.setPen(QPen(Qt::color1));
   p.setFont(QFont("Times",75,QFont::Bold));
   p.drawText(l.rect(),Qt::AlignCenter,"TOMKO BOMKO");
   p.end();

   pi.setMask(bmp);
   p.begin(&pi);
   p.drawPixmap(l.rect(),pi);
   p.end();

   l.setPixmap(pi);
   l.show();


   return a.exec();
}
