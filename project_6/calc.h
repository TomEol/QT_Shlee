#ifndef CALC_H
#define CALC_H

#include <QWidget>
#include <QLabel>
class QLineEdit;
class Button;
#include "lab_one.h"

class Calculator : public QWidget{
    Q_OBJECT
public:
    Calculator(QWidget *parent = 0);
private:
    Button *createButton(const QString &text, const char *member);
    void abort();
    bool calculate(double rightOperand, const QString &pendingOperator);

    double sumAccumulatedValue;
    double temporaryValue;
    QString lastAdditiveOperator;
    QString lastMultiplicativeOperator;
    bool waitingForSomeOperand;
    QLineEdit *display;
    static const int AMOUNT_OF_BUTTONS_DIGIT = 10;
    Button *digitButtons[AMOUNT_OF_BUTTONS_DIGIT];
    //----------------------
    Lab_one labs;
    QLabel *lb1;
    QLabel *lb2;
    QLabel *lb3;
    QLabel *lb4;

private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clearAll();
    //-------------------- lab:1-2-3
    void lab_oneClicked();
    void labelRead();
    void readMainDATA();
    void processing();
    void showAll();
    void clearData();
    void saveF();

};

#endif // CALC_H
