#include <QtWidgets>
#include "SyntaxHighlighter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextEdit txt;

    QFont font_local("Lucida Console",9,QFont::Normal);
    txt.document()->setDefaultFont(font_local);

    new SyntaxHighlighter(txt.document());;

    QPalette pal = txt.palette();
    pal.setColor(QPalette::Base,Qt::darkBlue);
    pal.setColor(QPalette::Text,Qt::yellow);
    txt.setPalette(pal);

    txt.show();
    txt.resize(640,480);

    QFile file(":/SyntaxHighlighter.cpp");
    file.open(QFile::ReadOnly);
    txt.setPlainText(QLatin1String(file.readAll()));


    return a.exec();
}
