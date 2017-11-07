#ifndef VALIDAT_H
#define VALIDAT_H

#include <QValidator>

class valid : public QValidator{
public:
    valid(QObject *parent):QValidator(parent){}

    virtual State validate(QString &str, int &pos) const{
        QRegExp rxp = QRegExp("[0-9]");
        if(str.contains(rxp))
            return Invalid;
        return Acceptable;
    }
};
#endif // VALIDAT_H
