#include <QtWidgets>

int main(int argc,char **argv){
    QApplication app(argc,argv);


    QWidget *wgt = new QWidget;
    QDial *p_dial = new QDial;
    QProgressBar *p_progressbar = new QProgressBar();
    p_progressbar->setOrientation(Qt::Vertical);

    p_dial->setRange(0,100);
    p_dial->setNotchTarget(5);
    p_dial->setNotchesVisible(true);
    p_dial->setWrapping(false);

    QObject::connect(p_dial,SIGNAL(valueChanged(int)),p_progressbar,SLOT(setValue(int)));

    QVBoxLayout *p_vL = new QVBoxLayout;
    p_vL->addWidget(p_dial);
    QHBoxLayout *p_hL = new QHBoxLayout;
    p_hL->addWidget(p_progressbar);
    p_hL->addLayout(p_vL);

    wgt->setLayout(p_hL);
    wgt->resize(700,500);
    wgt->show();

    return app.exec();
}
