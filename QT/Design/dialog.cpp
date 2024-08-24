#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow1.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pb_addwindow_clicked()
{
    MainWindow1 *new_window{new MainWindow1(this)};
    new_window->show();
}

