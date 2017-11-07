#include "brightanddark.h"
#include "ui_brightanddark.h"
#include <QDebug>

BrightAndDark::BrightAndDark(QString nameFileImg,QWidget *parent) :  QWidget(parent),
                                                                     ui(new Ui::BrightAndDark),
                                                                     name_file_img(nameFileImg)
{
    ui->setupUi(this);
    this->resize(800,800);
    ui->H_slider->setRange(-200,200);
    ui->H_slider->setTickInterval(5);
    ui->H_slider->setTickPosition(QSlider::TicksBelow);
    ui->H_slider->setValue(0);


    QPixmap img(":/" + name_file_img);
    img = img.scaled(QSize(500,500),Qt::KeepAspectRatio);
    ui->label->setPixmap(img);
    ui->label->setAlignment(Qt::AlignCenter);

    connect(ui->H_slider,SIGNAL(valueChanged(int)),this,SLOT(brigthness(int)));
    connect(ui->invert_button_1,SIGNAL(clicked(bool)),this,SLOT(invert(bool)));


}

BrightAndDark::~BrightAndDark()
{
    delete ui;
}

void BrightAndDark::brigthness(const int value){
    QImage img_local(":/" + name_file_img);
    qint32 imgH = img_local.height();
    qint32 imgW = img_local.width();

    for(qint32 y = 0 ; y < imgH; ++y){
        QRgb *tempLine = reinterpret_cast<QRgb*>(img_local.scanLine(y));

        for(qint32 x = 0; x < imgW; ++x){
            int r = qRed(*tempLine) + value;
            int g = qGreen(*tempLine) + value;
            int b = qBlue(*tempLine) + value;
            int a = qAlpha(*tempLine) + value;

            *tempLine++ = qRgba(r > 255 ? 255: r < 0 ? 0 :r,
                                g > 255 ? 255: g < 0 ? 0 :g,
                                b > 255 ? 255: b < 0 ? 0 :b,
                                a
                                );
        }
    }
    QPixmap img = QPixmap::fromImage(img_local);
    img = img.scaled(QSize(500,500),Qt::KeepAspectRatio);
    ui->label->setPixmap(img);
}
void BrightAndDark::invert(const bool flag){
    QImage img_local(":/" + name_file_img);
    img_local.invertPixels(QImage::InvertRgba);
    QPixmap img = QPixmap::fromImage(img_local);
    img = img.scaled(QSize(500,500),Qt::KeepAspectRatio);
    ui->label->setPixmap(img);
}
