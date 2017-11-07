#include "lab_one.h"

inline int sNum(const QString &line,QVector<QString>&nData){
    QString local_line(line);
    QTextStream stream_text(&local_line);
    QString str , new_str;
    while(!stream_text.atEnd()){
        stream_text >> str;
        if(str[0].isDigit()){
            return str.toInt();
        }
        if(str[0] == '['){
            nData.push_back(str);
        }
    }
}

Lab_one::Lab_one(){
    int i = 0, start_column = 0, start_row = 0;

    QFile main_file(":/DATA.txt");
    if(!main_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream textStream(&main_file);
    QVector<QString>nData;

    start_column = sNum(textStream.readLine(),nData);
    start_row = sNum(textStream.readLine(),nData);
    int temp = sNum(textStream.readLine(),nData);

    while(i < start_column){
        QString key = nData[i];
        main_data.insert(key,QVector<double>());
        ++i;
    }
}
void Lab_one::setV(){
    QFile main_file(":/DATA.txt");
    if(!main_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream textStream(&main_file);
    QString line , key;
    //========================================= when find it - set data in vec
    line = textStream.readLine();
    line = textStream.readLine();
    while(key != "--*--"){
        line = textStream.readLine();
        if (!line[0].isDigit()){
            key = line;
            line = textStream.readLine();
            if(key == "--*--")
                 break;
        }
        main_data[key].push_back(line.toDouble());
     }
}
void Lab_one::getV(){
    QTextStream out(stdout);
    foreach (QString key, main_data.keys()) {
        out << key << " : ";
        foreach (double num, main_data.value(key)) {
            out << num <<" | ";
        }out<<"\n";
    }
}


//=== help function
void laba::SET_TABLE(QString &search_in_table,
                     QTextStream &file,
                     QVector<QVector<double>>&some_TABLE,
                     const QString &yourLine ){
    int i = 0;
    while(true){
            search_in_table = file.readLine();
            if(search_in_table == yourLine){
                    while(true){
                       search_in_table = file.readLine();
                       if(search_in_table == "END_TABLE_*" || search_in_table == "END_TABLE")
                           return;
                       some_TABLE.push_back(QVector<double>());
                       QTextStream ostr(&search_in_table);
                       QString str;
                       while(!ostr.atEnd()){
                           ostr >> str;
                           some_TABLE[i].push_back(str.toDouble());
                       }++i;
                    }
            }
    }
}


void laba::aver_pow_size(const QMap<QString,QVector<double>>&main_data,
                               QMap<QString,QVector<double>>&second_data,
                               QMap<QString,double>&final_result ){
    double sum = 0.0 , square_of_num = 0.0;
    foreach (QString key, main_data.keys()) {
        foreach (double num, main_data.value(key)) {
            second_data["(^"+key+")"].push_back(qPow(num,2));
            sum += num;
            square_of_num += pow(num,2);
        }
        sum = sum / main_data.value(key).size();
        final_result[("aver"+key)] = sum;
        final_result[("^"+key)] = square_of_num;
        final_result["[size]"] = main_data.value("[x]").size();
        sum = 0.0;
    }
}

void laba::covar(const QMap<QString,QVector<double>>&main_data,
                       QMap<QString,QVector<double>>&second_data,
                       QMap<QString,double>&final_result ){
    double covar = 0.0;
    int i = 0;
    QVector<QVector<double>>temp(2);

    foreach (QString key, main_data.keys()){
           foreach(double num, main_data.value(key)){
               second_data[key+"-aver"+key].push_back(num - final_result.value("aver"+key));
               temp[i].push_back(num - final_result.value("aver"+key));
           } ++i;
       }

    for(int first = 0;first < i; first +=2 ){
        for(int j = 0 ; j < temp[first].size(); ++j){
            covar += temp[first][j] * temp[first+1][j];
        }
    }

    covar = covar/temp[0].size();
    final_result["cov(X,Y)"] = covar / (temp.size()/2);
}

void laba::disp(const QMap<QString,QVector<double>>&main_data,
                      QMap<QString,QVector<double>>&second_data,
                      QMap<QString,double>&final_result){
    double disp = 0.0 , sum_x_averx = 0.0;
    foreach (QString key, main_data.keys()) {
        foreach (double num, main_data.value(key)) {
            disp += qPow((num - final_result.value("aver"+key)),2);
            second_data[key+"-aver"+key].push_back(num-final_result.value("aver"+key));
            sum_x_averx += num - final_result.value("aver"+key);
        }
        final_result["("+key+" - aver"+key+")^2"] = disp;
        disp = disp / main_data.value(key).size();
        final_result[("D"+key)] = disp;
        final_result[(key+"-aver"+key)] = sum_x_averx;
        disp = 0.0;
    }
}

void laba::peomp(const QMap<QString,QVector<double>>&main_data,
                       QMap<QString,double>&final_result){
    double b_one  = final_result.value("cov(X,Y)")/final_result.value("D[x]");
    double b_zero =  final_result.value("aver[y]") - (b_one*final_result.value("aver[x]"));
    final_result["[b0]"] = b_zero;
    final_result["[b1]"] = b_one;
}

void laba::corCoef(QMap<QString,double>&final_result){
    double sx = 0.0 , sy = 0.0 , Rxy = 0.0;
    sx = qSqrt(final_result.value("D[x]"));
    sy = qSqrt(final_result.value("D[y]"));
    Rxy = final_result.value("cov(X,Y)") / (sx*sy);
    final_result["sqrt[D(x)]"] = sx;
    final_result["sqrt[D(x)]"] = sy;
    final_result["R(xy)"] = Rxy;
}

void laba::determF(const QMap<QString,QVector<double>>&main_data,
                         QMap<QString,QVector<double>>&second_data,
                         QMap<QString,double>&final_result){
      foreach (double num, main_data.value("[x]")) {
          second_data["[y^]"].push_back((final_result.value("[b0]")+(final_result.value("[b1]")*num)));
      }
      double SSE = 0.0 , SSR = 0.0 , SST = 0.0 , R = 0.0;
      foreach (double num, main_data.value("[y]")) {
           SST += qPow((num - final_result.value("aver[y]")),2);
      }
      foreach (double num, second_data.value("[y^]")) {
           SSR += qPow((num - final_result.value("aver[y]")),2);
      }
      SSE = SST - SSR;
      R = SSR/SST;
      final_result["[SST]"] = SST;
      final_result["[SSE]"] = SSE;
      final_result["[SSR]"] = SSR;
      final_result["[R^2]"] = R;

      final_result["sqrt[Dx]"] = qSqrt(final_result.value("D[x]"));
      final_result["sqrt[Dy]"] = qSqrt(final_result.value("D[y]"));
      final_result["[Rxy]"] = final_result.value("cov(X,Y)")/ (final_result.value("sqrt[Dx]")*final_result.value("sqrt[Dy]"));
}

void laba::fisher(QMap<QString,double>&final_result){

    QVector<QVector<double>>FISHER_TABLE;
    QString yourLine, search_in_table;
    QTextStream in(stdin);
    int i = 0, k1 = 0 , size = 0;

    QFile fisherTable(":/FISHER.txt");
    if(!fisherTable.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream file(&fisherTable);

    yourLine = ("level a = " + QString::number(FISHER));
    SET_TABLE(search_in_table,file,FISHER_TABLE,yourLine);

    k1 = range.x;
    size = range.y;

    size  = size - 2 - 1;
    k1 = k1-1;

    final_result["[F-emp]"] = (final_result.value("[SSR]")/final_result.value("[SSE]"))*(final_result.value("[size]")-2);
    final_result["[F-kr]"] = FISHER_TABLE[size][k1];
}

void laba::stud(QMap<QString,double>&final_result){
     QVector<QVector<double>>STUD_TABLE;
     QString yourLine, search_in_table;
     QTextStream in(stdin);
     int i = 0, size = 0;
     QFile studTable(":/STUD.txt");
     if(!studTable.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
     QTextStream file(&studTable);
     yourLine = ("level a = " + QString::number(STUDENT));
     SET_TABLE(search_in_table,file,STUD_TABLE,yourLine);
     size = range.y;
     size = size - 2 - 1;

     //------------ standard error evaluation
     double standart_error_b0 = 0.0 , standart_error_b1 = 0.0 , standart_error_pow_e2 = 0.0;

     standart_error_pow_e2 = final_result.value("[SSE]") / (final_result.value("[size]") - 2);


     double second_part_b0 =   final_result.value("[size]") * final_result.value("([x] - aver[x])^2");
     double first_part_b0 = standart_error_pow_e2 * ( final_result.value("^[x]") / second_part_b0);
     standart_error_b0 = qSqrt(first_part_b0);

     double second_part_b1 =   1 / final_result.value("([x] - aver[x])^2");
     double first_part_b1 = standart_error_pow_e2 *  second_part_b1;
     standart_error_b1 = qSqrt(first_part_b1);

     final_result["[S-kr]"] = STUD_TABLE[0][size];
     final_result["[S-emp-b0]"] = standart_error_b0;
     final_result["[S-emp-b1]"] = standart_error_b1;
     final_result["standart_error_pow_e2"] =  qSqrt(standart_error_pow_e2);
}


void laba::hopeInterval(QMap<QString,double>&final_result){
   double hope_interval_b0_min = 0.0 , hope_interval_b0_max = 0.0;
   double hope_interval_b1_min = 0.0 , hope_interval_b1_max = 0.0;

   hope_interval_b0_min = final_result.value("[b0]") - (final_result.value("[S-emp-b0]")*final_result.value("[S-kr]"));
   hope_interval_b0_max = final_result.value("[b0]") + (final_result.value("[S-emp-b0]")*final_result.value("[S-kr]"));

   hope_interval_b1_min = final_result.value("[b1]") - (final_result.value("[S-emp-b1]")*final_result.value("[S-kr]"));
   hope_interval_b1_max = final_result.value("[b1]") + (final_result.value("[S-emp-b1]")*final_result.value("[S-kr]"));

   final_result[("[min_b0]")] = hope_interval_b0_min;
   final_result[("[max_b0]")] = hope_interval_b0_max;
   final_result[("[min_b1]")] = hope_interval_b1_min;
   final_result[("[max_b1]")] = hope_interval_b1_max;
}
void laba::t_test(QMap<QString,double>&final_result){
    double t = 0.0;
    t = (final_result.value("[Rxy]") * qSqrt(final_result.value("[size]")))/qSqrt(1-qPow(final_result.value("[Rxy]"),2));
    final_result["[t_test]"] = t;
}
void laba::spotF(QMap<QString,double>&final_result){
    QTextStream in(stdin);
    double new_x = 0.0 , new_y = 0.0;
    new_x = X/100;
    new_x = new_x * final_result.value("aver[x]");
    new_y = final_result.value("[b0]") + (final_result.value("[b1]") * new_x);
    final_result["[x*]"] = new_x;
    final_result["[^Y*]"] = new_y;
}
void laba::intervalF(QMap<QString,double>&final_result){
     double su = 0.0 , sE = 0.0;

     double part_su_0  =  qPow(final_result.value("[x*]")-final_result.value("aver[x]"),2);
     double part_su_1  =  part_su_0 / final_result.value("([x] - aver[x])^2");
     double part_su_2  = qSqrt( 1 +  ( 1/final_result.value("[size]") ) + part_su_1);
     su = final_result.value("standart_error_pow_e2") * part_su_2;

     double part_sE_2  = qSqrt(( 1/final_result.value("[size]") ) + part_su_1);
     sE = final_result.value("standart_error_pow_e2") * part_sE_2;

     final_result["[su]"] = su;
     final_result["[sE]"] = sE;

     double Forecast_of_a_specific_value_min = 0.0 , Average_Forecast_min = 0.0;
     double Forecast_of_a_specific_value_max = 0.0 , Average_Forecast_max = 0.0;

     Forecast_of_a_specific_value_min = final_result.value("[^Y*]") - final_result.value("[S-kr]")*su;
     Forecast_of_a_specific_value_max = final_result.value("[^Y*]") + final_result.value("[S-kr]")*su;

     Average_Forecast_min = final_result.value("[^Y*]") - final_result.value("[S-kr]")*sE;
     Average_Forecast_max = final_result.value("[^Y*]") + final_result.value("[S-kr]")*sE;

     final_result["Forecast_of_a_specific_value_min"] = Forecast_of_a_specific_value_min;
     final_result["Forecast_of_a_specific_value_max"] = Forecast_of_a_specific_value_max;

     final_result["Average_Forecast_min"] = Average_Forecast_min;
     final_result["Average_Forecast_max"] = Average_Forecast_max;

}

void laba::readStaticDATA(){
    //---------------------------------------------------------------
    QFile Table(":/STATIC.txt");
    if(!Table.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream file(&Table);
    //----------------------------------------------------------------
    QString str , strL;
    while(!file.atEnd()){
        str = file.readLine();
        //---------------------------
        if(str[0] == "S"){
            QTextStream loc(&str);
            while(!loc.atEnd()){
                loc >> strL;
                if(strL[0].isDigit())
                    STUDENT = strL.toDouble();
            }
        }
        //---------------------------
        if(str[0] == "F"){
            QTextStream loc(&str);
            while(!loc.atEnd()){
                loc >> strL;
                if(strL[0].isDigit())
                    FISHER = strL.toDouble();
            }
        }
        //---------------------------
        if(str[0] == "R"){
            QTextStream loc(&str);
            while(!loc.atEnd()){
                loc >> strL;
                if(strL[0].isDigit()){
                    range.x = strL.toDouble();
                    loc >> strL;
                    range.y = strL.toDouble();
                }
            }
        }
        //-----------------------------
        if(str[0] == "X"){
            QTextStream loc(&str);
            while(!loc.atEnd()){
                loc >> strL;
                if(strL[0].isDigit())
                    X = strL.toDouble();
            }
        }
    }
}
//======================================= main_process

void Lab_one::getR(){
    qDebug() << endl<<endl;
    foreach (QString key, final_result.keys()) {
          qDebug()  << key << " : " << final_result.value(key);
        }
}


void Lab_one::main_process(){
    //----------------------------------------------------------- processing
    laba::aver_pow_size(main_data,second_data,final_result);
    laba::disp(main_data,second_data,final_result);
    laba::covar(main_data,second_data,final_result);
    laba::peomp(main_data,final_result);
    laba::determF(main_data,second_data,final_result);

    //------------------------------
    laba::readStaticDATA();
    //------------------------------

    laba::fisher(final_result);
    laba::stud(final_result);
    laba::hopeInterval(final_result);
    laba::t_test(final_result);
    laba::spotF(final_result);
    laba::intervalF(final_result);

    getR();
}







