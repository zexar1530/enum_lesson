#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    stopwatch = new Stopwatch(this);
    QObject::connect(stopwatch, &Stopwatch::sig_TimeUpdate, this, &Widget::update_lb_time);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pb_Start_clicked(bool checked)
{
    if(checked){
        ui->pb_Start->setText("Stop");
        ui->pb_Circle->setEnabled(true);
        stopwatch->startTimer();
    } else {
        ui->pb_Start->setText("Start");
        ui->pb_Circle->setEnabled(false);
        stopwatch->stopTimer();
    }
}

void Widget::update_lb_time(QString& timestr)
{
    ui->lb_Time->setText(QString("Time %1").arg(timestr));
}


void Widget::on_pb_Circle_clicked()
{
    ui->textBrowser->append(stopwatch->get_circle());
}


void Widget::on_pb_Clear_clicked()
{
    stopwatch->reset_watch();
    ui->lb_Time->setText("Time");
    ui->textBrowser->clear();
//    ui->pb_Start->setText("Start");
//    ui->pb_Circle->setEnabled(false);
}

