#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QSlider *slider = new QSlider(Qt::Horizontal);
    QLabel  *label  = new QLabel("3");

    slider->setRange(0,15);
    slider->setPageStep(1);
    slider->setValue(0);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksBelow);
    QObject::connect(slider,SIGNAL(valueChanged(int)),label,SLOT(setNum(int)));

    QHBoxLayout *p_bL = new QHBoxLayout;
    p_bL->addWidget(slider);
    p_bL->addWidget(label);

    w.setLayout(p_bL);

    w.show();

    return a.exec();
}
