#ifndef RADIOPLAYER_H
#define RADIOPLAYER_H

#include <QObject>
#include <QTimer>
#include "bass.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>

class RadioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit RadioPlayer(QObject *parent = nullptr);
    ~RadioPlayer();

private:
    QTimer          *timer = 0;         // таймер считывания метаданных из потока
    HSTREAM         str;                // поток
    QString         url_radio;          // url радиостанции
    QString         track_name;         // название текущей композиции
    QString         library;            // какая библиотека используется BASS или QMediaPlayer
    QMediaPlayer    *player = 0;        // плеер для Qt
    QAudioOutput    *audiooutput = 0;   // аудиовыход потока Qt
    QString         *comments = 0;      // строка содержащая метаданные потока


private slots:
    void metadata();                    // считываем метаданные

signals:
    void track_signal(QString);         // сигнал передает название песни
    void isPlaying(bool);               // сигнал играет ли сейчас радио

public:
    void play();                        // запуск потока
    void stop();                        // остановить поток
    void play_radio(QString url);       // запуск радио
    void set_library(QString lib);      // устанавливаем значение library
    void init();                        // инициализация проигрывателя
    void set_volume(float level);         // регулируем уровень громкости
};



#endif // RADIOPLAYER_H
