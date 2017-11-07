#ifndef LAB_ONE_H
#define LAB_ONE_H

#include "econometrics.h"

class Lab_one : public Econometrics
{
    Q_OBJECT
public:
    Lab_one();
    void setStartData();

    void getV();
    void setV();
    void getR()
    ;
    void main_process();
    void clear();
    void save();

private:
    QMap<QString,QVector<double>>main_data;
    QMap<QString,QVector<double>>second_data;
    QMap<QString,double>final_result;
};

inline int sNum(const QString &line,QVector<QString>&nData);

#endif // LAB_ONE_H
