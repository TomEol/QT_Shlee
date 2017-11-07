#include "lab_one.h"

//*************************************************
inline int sNum(const QString &line,
                QVector<QString>&nData){
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
//********************************
Lab_one::Lab_one(){
    // just create empty vectors
}
void Lab_one::setStartData(){
    int i = 0, start_column = 0, start_row = 0;
    QFile main_file(":/DATA.txt");
    if(!main_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream textStream(&main_file);
    QVector<QString>nData;

    start_column = sNum(textStream.readLine(),nData);
    start_row = sNum(textStream.readLine(),nData);
    int temp = sNum(textStream.readLine(),nData); // check this item

    while(i < start_column){
        QString key = nData[i];
        main_data.insert(key,QVector<double>());
        ++i;
    }
}
//*********************************
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
//*********************************
void Lab_one::getV(){
    qDebug () << "\n getV \n";
    foreach (QString key, main_data.keys()) {
        qDebug () << key << " : ";
        foreach (double num, main_data.value(key)) {
            qDebug () << num <<" | ";
        }qDebug () <<"\n";
    }
}
//*********************************
void Lab_one::getR(){
    qDebug() << endl<<endl;
    foreach (QString key, final_result.keys()) {
          qDebug()  << key << " : " << final_result.value(key);
        }
}
void Lab_one::save(){

  QFile file("F:/_QT/_qt/ch_6/project_6/out.txt");
  file.open(QIODevice::Append);
  QTextStream out(&file);

  foreach (QString key, main_data.keys()) {
  out << "\r\n"<< key << " : ";
       foreach (double num, main_data.value(key)) {
         out << num <<" | ";
       }out << "\r\n";
   }

   foreach (QString key, final_result.keys()) {
            out << "\r\n" <<  key << " : " << final_result.value(key) << "\r\n";
   }
   file.close();
}
//*********************************

void Lab_one::clear(){
    second_data.clear();
    main_data.clear();
    final_result.clear();
    qDebug() << " clear is done ";
}
void Lab_one::main_process(){
    Econometrics_math::aver_pow_size(main_data,second_data,final_result);
    Econometrics_math::disp(main_data,second_data,final_result);
    Econometrics_math::covar(main_data,second_data,final_result);
    Econometrics_math::peomp(main_data,final_result);
    Econometrics_math::determF(main_data,second_data,final_result);
    Econometrics_math::fisher(final_result);
    Econometrics_math::stud(final_result);
    Econometrics_math::hopeInterval(final_result);
    Econometrics_math::t_test(final_result);
    Econometrics_math::spotF(final_result);
    Econometrics_math::intervalF(final_result);
}


