#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    /*Выделяем память под объекты классов.
     *Объект QSqlDatabase является основным классом низкого уровня,
     *в котором настраивается подключение к БД.
    */
    dataBase = new QSqlDatabase();

    simpleQuery = new QSqlQueryModel();




}

DataBase::~DataBase()
{
    delete dataBase;
    delete simpleQuery;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    /*  Класс QSqlDatabase представляет из себя интерфейс между
        кодом и БД. Он организует соединение с БД. Для подключения
        в конструктор класса необходимо передать драйвер БД и имя.
        В объекте может храниться несколько подключений, они различаются именами.
    */
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
    tableModel = new QSqlTableModel(this, *dataBase);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{
    //Для подключения необходимо передать параметры БД в объект класса.
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());
    //Для подключения к БД используется метод open(), который возвращает true в случае успешного подключения.
    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    //Сначала выбираем имя БД
    *dataBase = QSqlDatabase::database(nameDb);
    //Метод close() закрывает соединение с БД
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(requestType &request_type, QTableView* view)
{
    QString querry =      "SELECT title, description FROM film f "
                          "JOIN film_category fc on f.film_id = fc.film_id "
                          "JOIN category c on c.category_id = fc.category_id ";
    switch (request_type) {
    case requestAllFilms:
        tableModel->setTable("film");
        tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tableModel->setHeaderData(1, Qt::Horizontal, "Название");
        tableModel->setHeaderData(2, Qt::Horizontal, "Описание");
        tableModel->select();
        view->setModel(tableModel);
        view->setColumnHidden(0, true);
        for (int i = 3; i < tableModel->columnCount(); i++) {
                view->setColumnHidden(i, true);
        }
        break;
    case requestComedy:
        querry = querry + " WHERE c.name = 'Comedy'";
        simpleQuery->setQuery(querry, *dataBase);
        simpleQuery->setHeaderData(0, Qt::Horizontal, "Название");
        simpleQuery->setHeaderData(1, Qt::Horizontal, "Описание");
        view->setModel(simpleQuery);
        break;
    case requestHorrors:
        querry = querry + " WHERE c.name = 'Horror'";
        simpleQuery->setQuery(querry, *dataBase);
        simpleQuery->setHeaderData(0, Qt::Horizontal, "Название");
        simpleQuery->setHeaderData(1, Qt::Horizontal, "Описание");
        view->setModel(simpleQuery);
        break;
    default:
        break;
    }
    view->resizeColumnsToContents();
}


/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
