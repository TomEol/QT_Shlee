#include "econometrics.h"

Econometrics::Econometrics(QObject *parent) : QObject(parent)
{

}
void Econometrics_math::setStatic(const double &l1,
                                               const double &l2,
                                               const double &l3,
                                               const double &l4){
    FISHER  = l1;
    STUDENT = l2;
    SIZE    = l3;
    X       = l4;
}
//*****************************************************************************
//*****************************************************************************
void Econometrics_math::getStatic(){
    qDebug() << FISHER
        <<" "<< STUDENT
        <<" "<< SIZE
        <<" "<< X;
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::SET_TABLE(QTextStream &file,
                     QVector<QVector<double>>&TABLE,
                     const QString &line ){
    QString source;
    int i = 0;
    while(source != "END_TABLE"){
            source = file.readLine();
            if(source == line){
                    while(true){
                       source = file.readLine();
                       if(source == "END_TABLE"){
                           qDebug() << " not found table ";
                           return;
                       }
                       if(source == "END_TABLE_*"){
                           return;
                       }
                       TABLE.push_back(QVector<double>());
                       QTextStream ostr(&source);
                       QString str;
                       while(!ostr.atEnd()){
                           ostr >> str;
                           TABLE[i].push_back(str.toDouble());
                       }++i;
                    }
            }
    }
    qDebug() << " SET_TABLE good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::aver_pow_size(const QMap<QString,QVector<double>>&source,
                               QMap<QString,QVector<double>>&second_source,
                               QMap<QString,double>&destiny ){
    double sum = 0.0 , square_of_num = 0.0;
    foreach (QString key, source.keys()) {
        foreach (double num, source.value(key)) {
            second_source["(^"+key+")"].push_back(qPow(num,2));
            sum += num;
            square_of_num += pow(num,2);
        }
        sum = sum / source.value(key).size();
        destiny[("aver"+key)] = sum;
        destiny[("^"+key)] = square_of_num;
        destiny["[size]"] = source.value("[x]").size();
        sum = 0.0;
    }
    qDebug() << " aver_pow_size good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::covar(const QMap<QString,QVector<double>>&source,
                       QMap<QString,QVector<double>>&second_source,
                       QMap<QString,double>&destiny ){
    double covar = 0.0;
    int i = 0;
    QVector<QVector<double>>temp(2);

    foreach (QString key, source.keys()){
           foreach(double num, source.value(key)){
               second_source[key+"-aver"+key].push_back(num - destiny.value("aver"+key));
               temp[i].push_back(num - destiny.value("aver"+key));
           } ++i;
       }

    for(int first = 0;first < i; first +=2 ){
        for(int j = 0 ; j < temp[first].size(); ++j){
            covar += temp[first][j] * temp[first+1][j];
        }
    }

    covar = covar/temp[0].size();
    destiny["cov(X,Y)"] = covar / (temp.size()/2);
    qDebug() << " covar good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::disp(const QMap<QString,QVector<double>>&source,
                      QMap<QString,QVector<double>>&second_source,
                      QMap<QString,double>&destiny){
    double disp = 0.0 , sum_x_averx = 0.0;
    foreach (QString key, source.keys()) {
        foreach (double num, source.value(key)) {
            disp += qPow((num - destiny.value("aver"+key)),2);
            second_source[key+"-aver"+key].push_back(num-destiny.value("aver"+key));
            sum_x_averx += num - destiny.value("aver"+key);
        }
        destiny["("+key+" - aver"+key+")^2"] = disp;
        disp = disp / source.value(key).size();
        destiny[("D"+key)] = disp;
        destiny[(key+"-aver"+key)] = sum_x_averx;
        disp = 0.0;
    }
    qDebug() << " disp good ";
}
//******************************************************************************
//******************************************************************************  delete source
void Econometrics_math::peomp(const QMap<QString,QVector<double>>&source,
                       QMap<QString,double>&destiny){
    double b_one  = destiny.value("cov(X,Y)")/destiny.value("D[x]");
    double b_zero =  destiny.value("aver[y]") - (b_one*destiny.value("aver[x]"));
    destiny["[b0]"] = b_zero;
    destiny["[b1]"] = b_one;
    qDebug() << " peomp good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::corCoef(QMap<QString,double>&destiny){
    double sx = 0.0 , sy = 0.0 , Rxy = 0.0;
    sx = qSqrt(destiny.value("D[x]"));
    sy = qSqrt(destiny.value("D[y]"));
    Rxy = destiny.value("cov(X,Y)") / (sx*sy);
    destiny["sqrt[D(x)]"] = sx;
    destiny["sqrt[D(x)]"] = sy;
    destiny["R(xy)"] = Rxy;
    qDebug() << " corCoef good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::determF(const QMap<QString,QVector<double>>&source,
                         QMap<QString,QVector<double>>&second_source,
                         QMap<QString,double>&destiny){
      foreach (double num, source.value("[x]")) {
          second_source["[y^]"].push_back((destiny.value("[b0]")+(destiny.value("[b1]")*num)));
      }
      double SSE = 0.0 , SSR = 0.0 , SST = 0.0 , R = 0.0;
      foreach (double num, source.value("[y]")) {
           SST += qPow((num - destiny.value("aver[y]")),2);
      }
      foreach (double num, second_source.value("[y^]")) {
           SSR += qPow((num - destiny.value("aver[y]")),2);
      }
      SSE = SST - SSR;
      R = SSR/SST;
      destiny["[SST]"] = SST;
      destiny["[SSE]"] = SSE;
      destiny["[SSR]"] = SSR;
      destiny["[R^2]"] = R;

      destiny["sqrt[Dx]"] = qSqrt(destiny.value("D[x]"));
      destiny["sqrt[Dy]"] = qSqrt(destiny.value("D[y]"));
      destiny["[Rxy]"] = destiny.value("cov(X,Y)")/ (destiny.value("sqrt[Dx]")*destiny.value("sqrt[Dy]"));
      qDebug() << " determF good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::fisher(QMap<QString,double>&destiny){
    QVector<QVector<double>>FISHER_TABLE;
    QString yourLine;
    int k1 = 0 , size = 0;
    QFile fisherTable(":/FISHER.txt");
    if(!fisherTable.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream file(&fisherTable);
    yourLine = ("level a = " + QString::number(FISHER));
    SET_TABLE(file,FISHER_TABLE,yourLine);
    k1 = 1;
    size = SIZE;
    size  = size - 2 - 1;
    k1 = k1-1;
    destiny["[F-emp]"] = (destiny.value("[SSR]")/destiny.value("[SSE]"))*(destiny.value("[size]")-2);
    destiny["[F-kr]"] = FISHER_TABLE[size][k1];
    qDebug() << " Fisher good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::stud(QMap<QString,double>&destiny){
     QVector<QVector<double>>STUD_TABLE;
     QString yourLine;
     int i = 0, size = 0;
     QFile studTable(":/STUD.txt");
     if(!studTable.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
     QTextStream file(&studTable);
     yourLine = ("level a = " + QString::number(STUDENT));
     SET_TABLE(file,STUD_TABLE,yourLine);
     size = SIZE - 2 - 1;

     //------------ standard error evaluation
     double standart_error_b0 = 0.0 , standart_error_b1 = 0.0 , standart_error_pow_e2 = 0.0;

     standart_error_pow_e2 = destiny.value("[SSE]") / (destiny.value("[size]") - 2);


     double second_part_b0 =   destiny.value("[size]") * destiny.value("([x] - aver[x])^2");
     double first_part_b0 = standart_error_pow_e2 * ( destiny.value("^[x]") / second_part_b0);
     standart_error_b0 = qSqrt(first_part_b0);

     double second_part_b1 =   1 / destiny.value("([x] - aver[x])^2");
     double first_part_b1 = standart_error_pow_e2 *  second_part_b1;
     standart_error_b1 = qSqrt(first_part_b1);

     destiny["[S-kr]"] = STUD_TABLE[0][size];
     destiny["[S-emp-b0]"] = standart_error_b0;
     destiny["[S-emp-b1]"] = standart_error_b1;
     destiny["standart_error_pow_e2"] =  qSqrt(standart_error_pow_e2);
     qDebug() << " stud good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::hopeInterval(QMap<QString,double>&destiny){
   double hope_interval_b0_min = 0.0 , hope_interval_b0_max = 0.0;
   double hope_interval_b1_min = 0.0 , hope_interval_b1_max = 0.0;

   hope_interval_b0_min = destiny.value("[b0]") - (destiny.value("[S-emp-b0]")*destiny.value("[S-kr]"));
   hope_interval_b0_max = destiny.value("[b0]") + (destiny.value("[S-emp-b0]")*destiny.value("[S-kr]"));

   hope_interval_b1_min = destiny.value("[b1]") - (destiny.value("[S-emp-b1]")*destiny.value("[S-kr]"));
   hope_interval_b1_max = destiny.value("[b1]") + (destiny.value("[S-emp-b1]")*destiny.value("[S-kr]"));

   destiny[("[min_b0]")] = hope_interval_b0_min;
   destiny[("[max_b0]")] = hope_interval_b0_max;
   destiny[("[min_b1]")] = hope_interval_b1_min;
   destiny[("[max_b1]")] = hope_interval_b1_max;
   qDebug() << " hope interval good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::t_test(QMap<QString,double>&destiny){
    double t = 0.0;
    t = (destiny.value("[Rxy]") * qSqrt(destiny.value("[size]")))/qSqrt(1-qPow(destiny.value("[Rxy]"),2));
    destiny["[t_test]"] = t;
    qDebug() << " t_test good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::spotF(QMap<QString,double>&destiny){
    double new_x = 0.0 , new_y = 0.0;
    new_x = destiny.value("aver[x]") * (X/100);
    new_y = destiny.value("[b0]") + (destiny.value("[b1]") * new_x);
    destiny["[x*]"] = new_x;
    destiny["[^Y*]"] = new_y;
    qDebug() << " spotF good ";
}
//******************************************************************************
//******************************************************************************
void Econometrics_math::intervalF(QMap<QString,double>&destiny){
     double su = 0.0 , sE = 0.0;

     double part_su_0  =  qPow(destiny.value("[x*]")-destiny.value("aver[x]"),2);
     double part_su_1  =  part_su_0 / destiny.value("([x] - aver[x])^2");
     double part_su_2  = qSqrt( 1 +  ( 1/destiny.value("[size]") ) + part_su_1);
     su = destiny.value("standart_error_pow_e2") * part_su_2;

     double part_sE_2  = qSqrt(( 1/destiny.value("[size]") ) + part_su_1);
     sE = destiny.value("standart_error_pow_e2") * part_sE_2;

     destiny["[su]"] = su;
     destiny["[sE]"] = sE;

     double Forecast_of_a_specific_value_min = 0.0 , Average_Forecast_min = 0.0;
     double Forecast_of_a_specific_value_max = 0.0 , Average_Forecast_max = 0.0;

     Forecast_of_a_specific_value_min = destiny.value("[^Y*]") - destiny.value("[S-kr]")*su;
     Forecast_of_a_specific_value_max = destiny.value("[^Y*]") + destiny.value("[S-kr]")*su;

     Average_Forecast_min = destiny.value("[^Y*]") - destiny.value("[S-kr]")*sE;
     Average_Forecast_max = destiny.value("[^Y*]") + destiny.value("[S-kr]")*sE;

     destiny["Forecast_of_a_specific_value_min"] = Forecast_of_a_specific_value_min;
     destiny["Forecast_of_a_specific_value_max"] = Forecast_of_a_specific_value_max;

     destiny["Average_Forecast_min"] = Average_Forecast_min;
     destiny["Average_Forecast_max"] = Average_Forecast_max;
     qDebug() << " intervalF good ";

}
//******************************************************************************
//******************************************************************************
