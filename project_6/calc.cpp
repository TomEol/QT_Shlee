#include <QtWidgets>
#include <cmath>
#include "button.h"
#include "calc.h"

Calculator::Calculator(QWidget *parent):QWidget(parent){
    sumAccumulatedValue   = 0.0;
    temporaryValue        = 0.0;
    waitingForSomeOperand = true;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(25);

    QFont font = display->font();
    font.setPointSize(font.pointSize()+8);
    display->setFont(font);

    //-------------------------------------------------------------------------- draw digits
    for(int i = 0; i < AMOUNT_OF_BUTTONS_DIGIT;++i){
        digitButtons[i] = createButton(QString::number(i),SLOT(digitClicked()));
    }
    //--------------------------------------------------------------- point button
    Button *pointButton = createButton(tr("."),SLOT(pointClicked()));
    //--------------------------------------------------------------- change sign
    Button *changeSignButton = createButton(tr("\302\261"),SLOT(changeSignClicked()));
    //-----------------------------------------------------------------backspace button
    Button *backspaceButton = createButton("<-",SLOT(backspaceClicked()));
    //-----------------------clear all
    Button *clearAllButton = createButton("CE",SLOT(clearAll()));
    //----------------------- divide - multiplicative button
    Button *divisionButton = createButton(tr("\303\267"),SLOT(multiplicativeOperatorClicked()));
    Button *multiplicativeButton = createButton(tr("\303\227"),SLOT(multiplicativeOperatorClicked()));
    //----------------------- plus - minus button
    Button *plusButton = createButton(tr("+"),SLOT(additiveOperatorClicked()));
    Button *minusButton = createButton(tr("-"),SLOT(additiveOperatorClicked()));
    //----------------------- sqrt button
    Button *sqrtButton = createButton(tr("sqrt"),SLOT(unaryOperatorClicked()));
    //----------------------- pow button
    Button *powButton = createButton(tr("x\302\262"),SLOT(unaryOperatorClicked()));
    //----------------------- equal button
    Button *equalButton = createButton(tr("="),SLOT(equalClicked()));
    //===================================================================== lab one
    Button *lab_one = createButton(tr("LB1"),SLOT(lab_oneClicked()));
    Button *lab_two = createButton(tr("LB2"),SLOT(lab_twoClicked()));
    Button *lab_three = createButton(tr("LB3"),SLOT(lab_threeClicked()));

    //----------------------------- now add widgets in layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display,0,0,1,6);
    mainLayout->addWidget(backspaceButton,1,5);
    mainLayout->addWidget(clearAllButton,1,4);
    //-------------------------------------------------
    QHBoxLayout *p_hL = new QHBoxLayout;
    p_hL->addWidget(lab_one);
    p_hL->addWidget(lab_two);
    p_hL->addWidget(lab_three);
    //-------------------------------------------------
    QGridLayout *mainLayout2 = new QGridLayout;
    mainLayout2->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout2->addLayout(mainLayout,1,0);
    mainLayout2->addLayout(p_hL,0,0);

    for(int i = 1 ; i < AMOUNT_OF_BUTTONS_DIGIT;++i){
        int row = ((9-i)/3)+2;
        int column = ((i-1)%3)+1;
        mainLayout->addWidget(digitButtons[i],row,column);
    }

    mainLayout->addWidget(digitButtons[0],5,1);
    mainLayout->addWidget(pointButton,5,2);
    mainLayout->addWidget(changeSignButton,5,3);

    mainLayout->addWidget(divisionButton,2,4);
    mainLayout->addWidget(multiplicativeButton,3,4);
    mainLayout->addWidget(minusButton,4,4);
    mainLayout->addWidget(plusButton,5,4);

    mainLayout->addWidget(sqrtButton,2,5);
    mainLayout->addWidget(powButton,3,5);
    mainLayout->addWidget(equalButton,4,5);

    setLayout(mainLayout2);
    move(300,50);


    setWindowTitle(tr("Calculator"));
}
//---------------------------------------------------------- digits
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForSomeOperand) {
        display->clear();
        waitingForSomeOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}
//---------------------------------------------------------- sqrt - pow and so on
void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("sqrt")) {
        if (operand < 0.0) {
            abort();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abort();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForSomeOperand = true;
}
//----------------------------------------------------------
void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!lastMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, lastMultiplicativeOperator)) {
            abort();
            return;
        }
        qDebug() << "add oper ";
        display->setText(QString::number(temporaryValue));
        operand = temporaryValue;
        temporaryValue = 0.0;
        lastMultiplicativeOperator.clear();
    }
    if (!lastAdditiveOperator.isEmpty()) {
        if (!calculate(operand, lastAdditiveOperator)) {
            abort();
            return;
        }
        display->setText(QString::number(sumAccumulatedValue));
    } else {
        sumAccumulatedValue = operand;
    }

    lastAdditiveOperator = clickedOperator;
    waitingForSomeOperand = true;
}
//----------------------------------------------------------
void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!lastMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, lastMultiplicativeOperator)) {
            abort();
            return;
        }
        qDebug() << "mult oper ";
        display->setText(QString::number(temporaryValue));
    } else {
        temporaryValue = operand;
    }

    lastMultiplicativeOperator = clickedOperator;
    waitingForSomeOperand = true;
}
//----------------------------------------------------------
void Calculator::equalClicked()
{
    double operand = display->text().toDouble();

    if (!lastMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, lastMultiplicativeOperator)) {
            abort();
            return;
        }
        operand = temporaryValue;
        temporaryValue = 0.0;
        lastMultiplicativeOperator.clear();
    }
    if (!lastAdditiveOperator.isEmpty()) {
        if (!calculate(operand, lastAdditiveOperator)) {
            abort();
            return;
        }
        lastAdditiveOperator.clear();
    } else {
        sumAccumulatedValue = operand;
    }

    display->setText(QString::number(sumAccumulatedValue));
    sumAccumulatedValue = 0.0;
    waitingForSomeOperand = true;
}
//----------------------------------------------------------
void Calculator::pointClicked()
{
    if (waitingForSomeOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForSomeOperand = false;
}
//----------------------------------------------------------
void Calculator::changeSignClicked(){
    QString text = display->text();
    double value = text.toDouble();

    if(value > 0.0){
        text.prepend(tr("-"));
    }else if(value < 0.0){
        text.remove(0,1);
    }
    display->setText(text);
}
//----------------------------------------------------------
void Calculator::backspaceClicked(){
    if(waitingForSomeOperand)
        return;
    QString text = display->text();
    text.chop(1);
    if(text.isEmpty()){
        text = "0";
        waitingForSomeOperand = true;
    }
    display->setText(text);
}
//----------------------------------------------------------
void Calculator::clearAll(){
    sumAccumulatedValue = 0.0;
    temporaryValue = 0.0;
    lastAdditiveOperator.clear();
    lastMultiplicativeOperator.clear();
    display->setText("0");
    waitingForSomeOperand = true;
}
//----------------------------------------------------------
Button* Calculator::createButton(const QString &textForButton, const char *member){
    Button *button = new Button(textForButton);
    connect(button,SIGNAL(clicked()),this,member);
    return button;
}
//----------------------------------------------------------
void Calculator::abort(){
    clearAll();
    display->setText(tr("####"));
}
//----------------------------------------------------------
bool Calculator::calculate(double rightOperand, const QString &Operator)
{
    if (Operator == tr("+")) {
       sumAccumulatedValue += rightOperand;
    } else if (Operator == tr("-")) {
        sumAccumulatedValue -= rightOperand;
    } else if (Operator == tr("\303\227")) {
        temporaryValue *= rightOperand;
    } else if (Operator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        temporaryValue /= rightOperand;
    }
    return true;
}

//-------------------------------- slot for lab 1

void Calculator::labelRead(){
    double F  = lb1->text().toDouble();
    double S  = lb2->text().toDouble();
    double sz = lb3->text().toDouble();
    double x  = lb4->text().toDouble();
    Econometrics_math::setStatic(F,S,sz,x);
}
void Calculator::readMainDATA(){
    labs.setStartData();
    labs.setV();
}
void Calculator::processing(){
   labs.main_process();
}
void Calculator::showAll(){
    labs.getV();// get main vector
    labs.getR();// get result vector
}
void Calculator::clearData(){
     labs.clear();
}
void Calculator::saveF(){
    labs.save();
}
//---------------------------------------------------------
void Calculator::lab_oneClicked(){
    lb1 = new QLabel;
    lb2 = new QLabel;
    lb3 = new QLabel;
    lb4 = new QLabel;
    QWidget *wgt = new QWidget;
    //-----------------------------------------------------
    QLabel *p_label_FISHER = new QLabel("&Fisher:");
    QLineEdit *p_txt_FISHER = new QLineEdit;
    p_label_FISHER->setBuddy(p_txt_FISHER);
    //-----------------------------------------------------
    QLabel *p_label_STUDENT = new QLabel("&Student:");
    QLineEdit *p_txt_STUDENT = new QLineEdit;
    p_label_STUDENT->setBuddy(p_txt_STUDENT);
    //-----------------------------------------------------
    QLabel *p_label_size = new QLabel("&Size:");
    QLineEdit *p_txt_size = new QLineEdit;
    p_label_size->setBuddy(p_txt_size);
    //-----------------------------------------------------
    QLabel *p_label_x = new QLabel("&x%:");
    QLineEdit *p_txt_x = new QLineEdit;
    p_label_x->setBuddy(p_txt_x);
    //-----------------------------------------------------
    QPushButton *readF = new QPushButton("R_Static");
                    connect(p_txt_FISHER,SIGNAL(textEdited(QString)),
                            lb1,         SLOT(setText(QString)));
                    connect(p_txt_STUDENT,SIGNAL(textEdited(QString)),
                            lb2,          SLOT(setText(QString)));
                    connect(p_txt_size,SIGNAL(textEdited(QString)),
                            lb3,       SLOT(setText(QString)));
                    connect(p_txt_x,SIGNAL(textEdited(QString)),
                            lb4,    SLOT(setText(QString)));
                    connect(readF,SIGNAL(clicked(bool)),this,SLOT(labelRead()));

    QPushButton *readArray = new QPushButton("R_Array");
                 connect(readArray,SIGNAL(clicked(bool)),this,SLOT(readMainDATA()));
    QPushButton *processing = new QPushButton("Processing");
                 connect(processing,SIGNAL(clicked(bool)),this,SLOT(processing()));
    QPushButton *exit = new QPushButton("Exit");
                 connect(exit,SIGNAL(clicked(bool)),wgt,SLOT(close()));
    //QPushButton *saveTF = new QPushButton("save to file"); // not now )
    QPushButton *show = new QPushButton("Show");
                 connect(show,SIGNAL(clicked(bool)),this,SLOT(showAll()));

    QPushButton *clearD = new QPushButton("&Clear");
                 connect(clearD,SIGNAL(clicked(bool)),this,SLOT(clearData()));
    QPushButton *save_tF = new QPushButton("&Save t F");
                 connect(save_tF,SIGNAL(clicked(bool)),this,SLOT(saveF()));


    //-----------------------------------------------------
    //-----------------------------------------------------
    QGridLayout *p_boxG = new QGridLayout;
    QHBoxLayout *p_mainL = new QHBoxLayout;
    //************************************** static data
    p_boxG->addWidget(p_label_FISHER,3,0);
    p_boxG->addWidget(p_txt_FISHER,3,2);
    p_boxG->addWidget(lb1,3,5);
    //---------
    p_boxG->addWidget(p_label_STUDENT,4,0);
    p_boxG->addWidget(p_txt_STUDENT,4,2);
    p_boxG->addWidget(lb2,4,5);
    //---------
    p_boxG->addWidget(p_label_size,5,0);
    p_boxG->addWidget(p_txt_size,5,2);
    p_boxG->addWidget(lb3,5,5);
    //---------
    p_boxG->addWidget(p_label_x,6,0);
    p_boxG->addWidget(p_txt_x,6,2);
    p_boxG->addWidget(lb4,6,5);
    //---------
    //************************************* buttons
    p_boxG->addWidget(readF,0,0);
    p_boxG->addWidget(readArray,0,1);
    p_boxG->addWidget(processing,1,0);
    p_boxG->addWidget(show,1,1);
    p_boxG->addWidget(clearD,2,0);
    p_boxG->addWidget(save_tF,0,2);
    p_boxG->addWidget(exit,2,1);
    //************************************** main layout
    p_mainL->addLayout(p_boxG);
    p_mainL->addStretch(10);
    //------------------------- show widget
    wgt->setLayout(p_mainL);
    wgt->resize(450,250);
    wgt->move(600,50);
    wgt->show();
}



















