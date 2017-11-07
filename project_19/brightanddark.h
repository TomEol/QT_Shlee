#ifndef BRIGHTANDDARK_H
#define BRIGHTANDDARK_H

#include <QWidget>

namespace Ui {
class BrightAndDark;
}

class BrightAndDark : public QWidget
{
    Q_OBJECT
public:
    explicit BrightAndDark(QString nameFileImg,QWidget *parent = 0);
    ~BrightAndDark();
public slots:
    void brigthness(const int value);
    void invert(const bool flag);

private:
    QString name_file_img;
    Ui::BrightAndDark *ui;
};

#endif // BRIGHTANDDARK_H
