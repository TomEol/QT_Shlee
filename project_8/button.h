#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QtWidgets>

class Button : public QWidget
{
    Q_OBJECT
private:
    QPushButton  menuButton;
    QMenu        *p_menu;
    QCheckBox    *one_normal;
    QCheckBox    *two_not_norm;
    QGroupBox    gbox;
    QRadioButton *start ;
    QRadioButton *boost ;
    QRadioButton *stop ;
    QHBoxLayout  *local_layout ;
    QHBoxLayout  *p_hbL;
    QVBoxLayout  *p_vbL;
    QPushButton  *exitbutton;
public:
    explicit Button(QWidget *parent = nullptr);
signals:
public slots:
    void slotButtonClicked();
};

#endif // BUTTON_H
