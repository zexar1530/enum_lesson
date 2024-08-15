#include <QCoreApplication>
#include <QtSql>
#include <QtNetwork/QHostAddress>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase data;
    QHostAddress addr;
    addr.clear();
    return a.exec();
}
