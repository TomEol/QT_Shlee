#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   QLabel l;
   QPicture pi;
   QPainter p(&pi);

   p.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
   p.drawLine(0, 0, 200, 200);

   p.setBrush(QBrush(Qt::HorPattern,QPixmap(":/1.png")));
   p.drawEllipse(50,0,300,300);

   QLinearGradient gradient(0,0,800,800);
   gradient.setColorAt(0,Qt::green);
   gradient.setColorAt(0.5,Qt::blue);
   gradient.setColorAt(1,Qt::yellow);

   p.setBrush(gradient);
   p.drawRect(0,0,700,700);
   p.setRenderHint(QPainter::Antialiasing,true);

   p.end(); // Don't forget this line!

   l.resize(900,900);
   l.setPicture(pi);
   l.show();
   return a.exec();
}
