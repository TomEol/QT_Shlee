#include <QtWidgets>
#include "validat.h"

int main(int argc, char **argv){
    QApplication app(argc,argv);

    QWidget *p_widget_main = new QWidget;
    QLabel *p_label_txt = new QLabel("&Enter Name: ");
    QLineEdit *p_text = new QLineEdit;

    valid *p_valid = new valid(p_text);
    p_text->setValidator(p_valid);
    p_label_txt->setBuddy(p_text);

    QVBoxLayout *p_bvL = new QVBoxLayout;
    p_bvL->addWidget(p_label_txt);
    p_bvL->addWidget(p_text);

    p_widget_main->setLayout(p_bvL);
    p_widget_main->resize(300,300);
    p_widget_main->show();


    return app.exec();
}
