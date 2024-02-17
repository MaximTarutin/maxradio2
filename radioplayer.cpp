#include "radioplayer.h"
#include <QDebug>

RadioPlayer::RadioPlayer(QObject *parent)
    : QObject{parent}
{
    BASS_Init (-1, 44100, 0 , 0, 0);
    BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST, 1);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &RadioPlayer::metadata);
}

RadioPlayer::~RadioPlayer()
{
    delete timer;
    BASS_StreamFree(str);                   //освободить поток
    BASS_PluginFree(0);
}

// ----------------------------- запустить воспроизведение ----------------------------------

void RadioPlayer::play()
{
    BASS_ChannelPlay(str, 0);
    timer->start(1);
}

// ------------------------------- остановить воспроизведение --------------------------------

void RadioPlayer::stop()
{
    BASS_ChannelStop(str);
    timer->stop();
}

// ----------------------------- читаем метаданные из потока ----------------------------------

void RadioPlayer::metadata()
{
    const char *comments = BASS_ChannelGetTags(str, BASS_TAG_META);
    if(comments)
    {
        qDebug() << comments;
    }
}

// -------------------- включить поток радио по заданному url -----------------------------------

void RadioPlayer::play_radio(QString url)
{
    BASS_ChannelStop(str);//остановить проигрывание
    BASS_StreamFree(str);//освободить поток
    str=BASS_StreamCreateURL(url.toStdString().c_str(), 0, 0, NULL, 0);     // загрузка в поток
    BASS_ChannelPlay(str, 0);                                               // проигрывание потока
    timer->start(1000);
}

// --------------------- устанавливаем значение library ----------------------------------------

void RadioPlayer::set_library(QString lib)
{
    library = lib;
}
