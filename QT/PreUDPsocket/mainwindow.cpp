#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendDataToGUI, this, &MainWindow::DisplayData);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend, "TIME");
        timer->start(TIMER_DELAY);

    });

    connect(this, &MainWindow::sig_sendData, this, [&]{

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);
        QHostAddress ip = QHostAddress::LocalHost;
        QString inputText = ui->te_inputData->toPlainText();
        outStr << ip.toString() << inputText;

        udpWorker->SendDatagram(dataToSend, "DATA");

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}


void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));


}

void MainWindow::DisplayData(QByteArray data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }
    QDataStream inStr(&data, QIODevice::ReadOnly);
    QString ip;
    QString inputText;
    inStr >> ip >> inputText;
    ui->te_result->append("Принято сообщение от: " + ip);
    ui->te_result->append(QString("Размер сообщения(байт) %1").arg(inputText.size()));
    ui->te_result->append(QString("Принято пакетов %1").arg(counterPck));
}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}


void MainWindow::on_pb_sendData_clicked()
{
    emit sig_sendData();
}

