#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pb_toggled(bool checked);

    void on_progress_valueChanged(int value);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
