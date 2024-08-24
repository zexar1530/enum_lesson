#include "mainwindow.h"
#include "mainwindow1.h"
#include "./ui_mainwindow.h"
#include "./ui_mainwindow1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_addwindow_clicked()
{
    //MainWindow1* new_window = new MainWindow1(this);
    MainWindow1 *new_window{new MainWindow1(this)};
    new_window->show();

}

