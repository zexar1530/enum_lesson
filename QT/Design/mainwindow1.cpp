#include "mainwindow1.h"
#include "ui_mainwindow1.h"

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui_1(new Ui::MainWindow1)
{
    ui_1->setupUi(this);
}

MainWindow1::~MainWindow1()
{
    delete ui_1;
}
