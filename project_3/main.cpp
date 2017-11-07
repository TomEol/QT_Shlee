#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>

QTextStream qtin(stdin);
QTextStream qtout(stdout);

void errorToFile(QtMsgType type,const QMessageLogContext &context,const QString &msg){
    QFile file("protocol.txt");
    QTextStream out(&file);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;

    switch(type){
    case QtDebugMsg:
         out << " Debug: "<<msg <<", "<<context.file <<endl; break;
    case QtWarningMsg:
         out << " Debug: "<<msg<<", "<<context.file<<endl; break;
    case QtCriticalMsg:
         out << " Debug: "<<msg<<", "<<context.file<<endl; break;
    case QtFatalMsg:
         out <<" Debug: "<<msg<<", "<<context.file<<endl; break;
         abort();
    }
}
void textToFile(const QString &msg){
    QFile file("just_text.txt");
    QTextStream out(&file);

    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
        return;

    out << " Debug: "<<msg <<", " <<endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInstallMessageHandler(errorToFile);

    QString yourText;
    yourText = qtin.readLine();
    textToFile(yourText);
    qDebug() << yourText;


    return a.exec();
}

