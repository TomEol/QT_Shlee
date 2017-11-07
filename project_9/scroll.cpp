#include <QtWidgets>

int main(int argc,char **argv){
    QApplication app(argc,argv);

    QWidget *wgt = new QWidget;
    QLCDNumber *lcdisplay = new QLCDNumber(4);
    QScrollBar *scrollbarH = new QScrollBar(Qt::Horizontal);
    QScrollBar *scrollbarV = new QScrollBar(Qt::Vertical);

    QObject::connect(scrollbarH,SIGNAL(valueChanged(int)),lcdisplay,SLOT(display(int)));
    QObject::connect(scrollbarV,SIGNAL(valueChanged(int)),lcdisplay,SLOT(display(int)));

    QVBoxLayout *p_vL = new QVBoxLayout;
    p_vL->addWidget(lcdisplay);
    p_vL->addStretch(10);
    p_vL->addWidget(scrollbarH);
    QHBoxLayout *p_hL = new QHBoxLayout;
    p_hL->addLayout(p_vL);
    p_hL->addWidget(scrollbarV);
    //p_hL->addStretch(10);

    wgt->setLayout(p_hL);
    wgt->resize(700,100);
    wgt->show();

    return app.exec();
}

