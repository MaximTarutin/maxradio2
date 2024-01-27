#ifndef DATABASERADIO_H
#define DATABASERADIO_H

#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>

class DataBaseRadio
{
public:
    DataBaseRadio();
    ~DataBaseRadio();

    std::list <QString> proba();

    void open_database();                       // открываем базу данных
    void init_database();                       // Инициализация базы данных
    std::list <QString> read_groups_db();       // Возвращает список групп радиостанций
    std::list <QString> read_name_db();         // Возвращает список радиостанций
    std::list <QString> read_url_db();          // Возвращает список url радиостанций

};

#endif // DATABASERADIO_H
