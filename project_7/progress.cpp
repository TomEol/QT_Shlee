#include "progress.h"
#include <QtWidgets>
#include <QDebug>

Progress::Progress(QWidget *parent):QWidget(parent),local_step(0){
    p_progress = new QProgressBar;
    p_progress->setRange(0,25);
    p_progress->setMinimumWidth(800);
    p_progress->setAlignment(Qt::AlignCenter);

    QLabel *p_one_L = new QLabel("login");
    QLabel *p_two_L = new QLabel("id");
    QLineEdit * p_lineE = new QLineEdit;
    QSpinBox *p_spinB = new QSpinBox;
    QPushButton *pb_exit = new QPushButton("&EXIT");

    connect(pb_exit,SIGNAL(clicked()),this,SLOT(close()));
    connect(p_spinB,SIGNAL(valueChanged(const int &)),this,SLOT(step(const int&)));
    connect(p_lineE,SIGNAL(textChanged(const QString &)), this, SLOT(text_slot(const QString &)));

    QVBoxLayout *p_vbL = new QVBoxLayout;
    QHBoxLayout *p_hbL = new QHBoxLayout;

    QLCDNumber *p_lcd = new QLCDNumber;
    p_lcd->setSegmentStyle(QLCDNumber::Filled);
    p_lcd->setFixedHeight(35);

    connect(p_spinB,SIGNAL(valueChanged(int)),p_lcd,SLOT(display(int)));

    p_hbL->addWidget(p_lcd);

    p_hbL->addWidget(p_one_L);
    p_hbL->addWidget(p_lineE);
    p_hbL->addWidget(p_two_L);
    p_hbL->addWidget(p_spinB);
    p_hbL->addWidget(pb_exit);
    p_hbL->addStretch(10);

    p_vbL->addLayout(p_hbL);
    p_vbL->addStretch(10);
    p_vbL->addWidget(p_progress);

    this->setLayout(p_vbL);
}


void Progress::step(const int i){
    p_progress->setValue(i);
}
void Progress::text_slot(const QString i){
   if ( i == "done"){
       reset();
   }
   if( i == "pass")
       step(1);
}

void Progress::reset(){
    local_step = 0;
    p_progress->reset();
}

