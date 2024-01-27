#include "maxradio_database.h"
#include <QDir>

Maxradio_DataBase::Maxradio_DataBase(QObject *parent)
    : QObject{parent}
{

}

// ----------------------- Открытие базы данных -------------------------------------

void Maxradio_DataBase::open_database()
{
    QString path;

#ifdef Q_OS_WIN                                 // Создаем файл базы данных (путь для windows)
    path = "maxradio.db";
#endif

#ifdef Q_OS_LINUX                               // Путь в Linux
    path = QDir::homePath()+"/.maxradio.db";
#endif

    QSqlDatabase maxradio_db = QSqlDatabase::addDatabase("QSQLITE");
    maxradio_db.setDatabaseName(path);
    maxradio_db.open();
}

// --------------------- Инициализация базы данных ----------------------------------------

void Maxradio_DataBase::init_database()
{
    QSqlQuery query;
    int count = 0;

    query.exec("SELECT COUNT(*) FROM maxradio_table");              // Проверяем не пустая ли база
    while(query.next())
    {
        count++;
    }

    if(count == 0)
    {
        query.exec("CREATE TABLE maxradio_table ("
                   "groups STRING, name STRING, url STRING, UNIQUE(url));");
        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Рок', 'Наше радио', 'http://nashe.streamr.ru/nashe-128.mp3')");
        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Рок', 'Maximum', 'https://maximum.hostingradio.ru/maximum96.aacp')");
        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Рок', 'Русский рок', 'https://hls.amgradio.ru/radio/rusrockhd.m3u8')");
        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Рок', 'Ангелов радио', 'https://5.restream.one/1143_1')");
        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Рок', 'Неслучайное радио', 'https://5.restream.one/1360_1')");


        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Поп', 'Европа плюс', 'http://ep128.hostingradio.ru:8030/ep128')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Поп', 'Ретро FM', 'http://retroserver.streamr.ru:8043/retro256.mp3')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Поп', 'Маруся-FM','https://str1.pcradio.ru/marusya_fm-med')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Поп', 'Радио Ваня','https://icecast-radiovanya.cdnvideo.ru/radiovanya')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Поп', 'Радио дача','http://listen5.vdfm.ru:8000/dacha')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Поп', 'Hit FM','https://hitfm.hostingradio.ru/hitfm96.aacp')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Поп', 'Пассаж','http://listen.radiopassazh.ru/mp3-128')");
        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Поп', 'Русское радио', "
                   "'https://rusradio.hostingradio.ru/rusradio96.aacp')");

        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Реп, хип-хоп', 'Зайцев FM - Rap','https://str1.pcradio.ru/rad_zcvfmrp-med')");

        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Танцевальная', 'NRJ',"
                   "'https://srv21.gpmradio.ru:8443/stream/air/aac/64/99')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Танцевальная', 'DFM',"
                   "'https://str1.pcradio.ru/dfm_moscow-med')");

        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Шансон', 'радио Шансон','http://chanson.hostingradio.ru:8041/chanson128.mp3')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Шансон', 'За друзей','http://listen2.myradio24.com:9000/8144')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Шансон', 'Ночной звонок','https://listen7.myradio24.com/74828')");


        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Юмор', 'Comedy радио','https://srv21.gpmradio.ru:8443/stream/air/aac/64/202')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Юмор', 'Юмор FM','https://srv21.gpmradio.ru:8443/stream/air/aac/64/102')");



        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Детское', 'Детское радио','https://srv21.gpmradio.ru:8443/stream/air/aac/64/199')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Детское', 'Детский хит','https://str1.pcradio.ru/rad_mgdt-med')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Детское', 'Мульти-пульти','https://str1.pcradio.ru/Kinder-med')");


        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Новости', 'Вести FM','https://str1.pcradio.ru/radiovesti_ru-med')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Новости', 'Комерсант FM','http://kommersant77.hostingradio.ru:8016/kommersant64.mp3')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Новости', 'Комсомольская правда','http://kraskp.ru:8000/mskregion')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Новости', 'радио России','http://91.228.66.62:8000/live')");
        query.exec("INSERT INTO maxradio_table (groups, name, url) "
                   "VALUES ('Новости', 'Маяк','http://icecast.vgtrk.cdnvideo.ru/mayakfm_mp3_128kbps')");


        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Классика', 'Радио классик', 'http://jfm1.hostingradio.ru:14536/rcstream.mp3')");
        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Классика', 'Радио культура', 'http://icecast.vgtrk.cdnvideo.ru/kulturafm')");

        query.exec("INSERT INTO maxradio_table (groups, name, url)"
                   "VALUES ('Другое', 'TarutinRadio', "
                   "'https://hls.amgradio.ru/radio/rusrockhd.m3u8')");
    }
}
