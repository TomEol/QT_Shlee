#include "button.h"

Button::Button(QWidget *parent) : QWidget(parent),menuButton("Menue"),gbox("&Triggers")
{
    exitbutton = new QPushButton("&exit");
    connect(exitbutton,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
    p_menu = new QMenu(&menuButton);
    //------------------------------------------------
    one_normal = new QCheckBox("&Light");
    one_normal->setChecked(true);
    connect(one_normal,SIGNAL(clicked(bool)),this,SLOT(slotButtonClicked()));
    //------------------------------------------------
    two_not_norm = new QCheckBox("! normal ");
    two_not_norm->setTristate(true);
    two_not_norm->setCheckState(Qt::PartiallyChecked);
    //------------------------------------------------
    p_menu->addAction("Open");
    p_menu->addAction("Save");
    p_menu->addAction("Save as");
    p_menu->addAction("Close");
    menuButton.setMenu(p_menu);
    //-----------------------------------------------
    start = new QRadioButton("&start");
    boost = new QRadioButton("&boost");
    stop  = new QRadioButton("&stop");
    stop->setChecked(true);
    connect(start,SIGNAL(clicked()),this,SLOT(slotButtonClicked()));
    connect(boost,SIGNAL(clicked()),this,SLOT(slotButtonClicked()));
    connect(stop,SIGNAL(clicked()),this,SLOT(slotButtonClicked()));
    //------------------------------------------------
    local_layout = new QHBoxLayout;
    local_layout->addWidget(start);
    local_layout->addWidget(boost);
    local_layout->addWidget(stop);
    gbox.setLayout(local_layout);
    //-----------------------------------------------
    p_hbL = new QHBoxLayout;
    p_vbL = new QVBoxLayout;
    //------------------------------------------------
    p_hbL->addWidget(&menuButton);
    p_hbL->addWidget(&gbox);
    p_hbL->addStretch(10);
    p_hbL->addLayout(p_hbL);
    p_hbL->addWidget(one_normal);
    p_hbL->addWidget(two_not_norm);
    //**********************
    p_vbL->addLayout(p_hbL);
    p_vbL->addStretch(10);
    p_vbL->addWidget(exitbutton);
    p_vbL->addStretch(10);
    //-----------------------------------------------
    this->setLayout(p_vbL);
    this->resize(550,150);
    this->move(150,150);

    slotButtonClicked();

}

void Button::slotButtonClicked(){
    QPalette pal = palette();
    int nLight = gbox.isChecked() ? 150 : 80;
    if(start->isChecked()){
        pal.setColor(backgroundRole(),QColor(Qt::red).light(nLight));
    }
    else if(boost->isChecked()){
        pal.setColor(backgroundRole(),QColor(Qt::green).light(nLight));
    }
    else{
        pal.setColor(backgroundRole(),QColor(Qt::blue).light(nLight));
    }
    setPalette(pal);
}









