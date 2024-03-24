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

    void open_database();                           // открываем базу данных
    void init_database();                           // Инициализация базы данных
    void reset_database();                          // сброс базы данных
    void add_radio(QString group, QString name,
                   QString url);                    // добавляем радиостанцию в базу данных
    void delete_radio(QString nameRadio);           // удаляем радиостанцию по имени
    std::list <QString> read_groups_db();           // Возвращает список групп радиостанций
    std::list <QString> read_name_db();             // Возвращает список радиостанций
    std::list <QString> read_url_db();              // Возвращает список url радиостанций
    QString get_url_radio(QString n);               // Возвращает url по имени радио
};

#endif // DATABASERADIO_H
