#ifndef ECONOMETRICS_H
#define ECONOMETRICS_H

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

class Econometrics : public QObject
{
    Q_OBJECT
public:
    explicit Econometrics(QObject *parent = nullptr);
private:

};


namespace Econometrics_math {

static double FISHER  ;
static double STUDENT ;
static double X       ;
static double SIZE    ;

void setStatic(const double &l1,const double &l2,const double &l3,const double &l4);
void getStatic();

 //======================================================================== help function
void SET_TABLE(QTextStream &file,
               QVector<QVector<double>>&TABLE,
               const QString &line );
 //========================================================================
void aver_pow_size(const QMap<QString,QVector<double>>&source,
                         QMap<QString,QVector<double>>&second_source,
                         QMap<QString,double>&destiny );
 //========================================================================
void covar(const QMap<QString,QVector<double>>&source,
                 QMap<QString,QVector<double>>&second_source,
                 QMap<QString,double>&desiny );
 //========================================================================
void disp(const QMap<QString,QVector<double>>&source,
                QMap<QString,QVector<double>>&second_source,
                QMap<QString,double>&destiny);
 //========================================================================
void peomp(const QMap<QString,QVector<double>>&source,
                 QMap<QString,double>&destiny);
 //========================================================================
void corCoef(QMap<QString,double>&destiny);
 //========================================================================
void determF(const QMap<QString,QVector<double>>&source,
                   QMap<QString,QVector<double>>&second_source,
                   QMap<QString,double>&destiny);
 //========================================================================
void fisher(QMap<QString,double>&destiny);
 //========================================================================
void stud(QMap<QString,double>&destiny);
 //========================================================================
void hopeInterval(QMap<QString,double>&destiny);
 //========================================================================
void spotF(QMap<QString,double>&destiny);
 //========================================================================
void intervalF(QMap<QString,double>&destiny);
 //========================================================================
void t_test(QMap<QString,double>&destiny);
 //========================================================================
}



#endif // ECONOMETRICS_H
