#ifndef PROGRESS_H
#define PROGRESS_H

#include <QWidget>
class QProgressBar;
class QLCDNumber;


class Progress: public QWidget{
    Q_OBJECT
private:
    QProgressBar *p_progress;
    int local_step;
public:
    Progress(QWidget *parent = 0);
public slots:
    void step(const int i);
    void reset();
    void text_slot(const QString i);
};

#endif // PROGRESS_H
