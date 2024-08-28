#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QTime>

class Stopwatch : public QObject {
    Q_OBJECT

public:
    Stopwatch(QObject* parent = nullptr) : QObject(parent){
        timer = new QTimer(this);
        timer->setInterval(100);
        time.setHMS(0, 0, 0, 0);
        timecircle.setHMS(0, 0, 0, 0);
        QObject::connect(timer, QTimer::timeout, this, Stopwatch::timeUpdate);
    }

    ~Stopwatch(){}

    void timeUpdate(){
        time = time.addMSecs(100);
        QString temp_str = time.toString("hh:mm:ss.z");
        emit sig_TimeUpdate(temp_str);
    }

    void startTimer(){
        timer->start();
    }

    void stopTimer(){
        timer->stop();
    }

    QString& get_circle(){
        count++;
        str = "Circle № " + QString::number(count) + " Time: " + QString::number(timecircle.secsTo(time)) + "sec";
        timecircle = time;
        return str;
    }

    void reset_watch(){
        timer->stop();
        time.setHMS(0, 0, 0, 0);
        timecircle.setHMS(0, 0, 0, 0);
        count = 0;
    }

private:
    QTimer* timer;
    QTime time;
    QTime timecircle;
    uint count = 0;
    QString str = "";

signals:
    void sig_TimeUpdate(QString&);
};

#endif // STOPWATCH_H
