#ifndef MAXRADIO_DATABASE_H
#define MAXRADIO_DATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QDir>

class Maxradio_DataBase : public QObject
{
    Q_OBJECT
public:
    explicit Maxradio_DataBase(QObject *parent = nullptr);

    void open_database();                       // открываем базу данных
    void init_database();                       // Инициализация базы данных


};

#endif // MAXRADIO_DATABASE_H
