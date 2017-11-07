#ifndef LAB_ONE_H
#define LAB_ONE_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <ctype.h>
#include <iomanip>
#include <iostream>
#include <QDebug>
#include <QMap>
#include <QtMath>
#include <numeric>

inline int sNum(const QString &line,QVector<QString>&nData);

class Lab_one : public QObject
{
    Q_OBJECT
public:
    Lab_one();
    void getV();
    void setV();
    void getR();
    void main_process();
private:
    QMap<QString,QVector<double>>main_data;
    QMap<QString,QVector<double>>second_data;
    QMap<QString,double>final_result;
};

namespace laba {

struct RANGE
{
    int x;
    int y;

    RANGE():x(0),y(0){}
    RANGE(int _x,int _y):x(_x),y(_y){}
};
//-------------------------
static double FISHER;
static double STUDENT;
static double X;
static RANGE range;

//-------------------------
void readStaticDATA();
 //======================================================================== help function
void SET_TABLE(QString &search_in_table,
               QTextStream &file,
               QVector<QVector<double>>&some_TABLE,
         const QString &yourLine );
 //========================================================================
void aver_pow_size(const QMap<QString,QVector<double>>&main_data,
                         QMap<QString,QVector<double>>&second_data,
                         QMap<QString,double>&final_result );
 //========================================================================
void covar(const QMap<QString,QVector<double>>&main_data,
                 QMap<QString,QVector<double>>&second_data,
                 QMap<QString,double>&final_result );
 //========================================================================
void disp(const QMap<QString,QVector<double>>&main_data,
                QMap<QString,QVector<double>>&second_data,
                QMap<QString,double>&final_result);
 //========================================================================
void peomp(const QMap<QString,QVector<double>>&main_data,
                 QMap<QString,double>&final_result);
 //========================================================================
void corCoef(QMap<QString,double>&final_result);
 //========================================================================
void determF(const QMap<QString,QVector<double>>&main_data,
                   QMap<QString,QVector<double>>&second_data,
                   QMap<QString,double>&final_result);
 //========================================================================
void fisher(QMap<QString,double>&final_result);
 //========================================================================
void stud(QMap<QString,double>&final_result);
 //========================================================================
void hopeInterval(QMap<QString,double>&final_result);
 //========================================================================
void spotF(QMap<QString,double>&final_result);
 //========================================================================
void intervalF(QMap<QString,double>&final_result);
 //========================================================================
void t_test(QMap<QString,double>&final_result);
 //========================================================================
}

#endif // LAB_ONE_H
