#ifndef RADIOPLAYER_H
#define RADIOPLAYER_H

#include <QObject>
#include <QTimer>
#include "bass.h"

class RadioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit RadioPlayer(QObject *parent = nullptr);
    ~RadioPlayer();

private:
    QTimer          *timer;             // таймер считывания метаданных из потока
    HSTREAM         str;                // поток
    QString         library;            // какая библиотека используется BASS или QMediaPlayer

private slots:
    void metadata();                    // считываем метаданные

public:
    void play();                        // запуск потока
    void stop();                        // остановить поток
    void play_radio(QString url);       // запуск радио
    void set_library(QString lib);      // устанавливаем значение library

signals:

};

#endif // RADIOPLAYER_H
