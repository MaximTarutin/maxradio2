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
};

#endif // DATABASERADIO_H
