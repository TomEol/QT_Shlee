#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("Coursier");
    font.setPointSize(15);

    QTextEdit *txt = new QTextEdit;

    QRgb rgb = qRgb(255,0,0);
    QColor color;
    color.setRgb(rgb);

    QPalette pal = txt->palette();

    pal.setColor(QPalette::Text,color);

    txt->setFont(font);
    txt->setPalette(pal);
    txt->resize(500,500);
    txt->show();


    return a.exec();
}
