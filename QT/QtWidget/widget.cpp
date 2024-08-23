#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //------Имена кнопкам-------
    ui->rb1->setText("Radio 1");
    ui->rb2->setText("Radio 2");
    ui->rb1->setChecked(true);

    //--------добавим Combo Box-------
    for(int i{}; i < 10; i++){
        ui->cmb->addItem(QString("Element %1").arg(i));
    }

    //---меняем название кнопки и ее тип-------
    ui->pb->setText("&Toogle");
    ui->pb->setCheckable(true);
    ui->pb->setStyleSheet("background-color:green;");

    //-----Пронгресс бар-------------------
    ui->progress->setMinimum(0);
    ui->progress->setMaximum(10);
    ui->progress->setValue(0);
    ui->progress->setTextVisible(true);
}

Widget::~Widget()
{
    delete ui; 
}


void Widget::on_pb_toggled(bool checked)
{
    if(ui->progress->value()==ui->progress->maximum())
        ui->progress->reset();
    if(checked){
        ui->progress->setValue(ui->progress->value()+1);
    } else{
        ui->progress->setValue(ui->progress->value()+1);
        ui->pb->setStyleSheet("background-color:red;"); //просто поменяем цве, а так условие checked можно опустить!
    }
}

void Widget::on_progress_valueChanged(int value) // не стал использовать!
{

}

