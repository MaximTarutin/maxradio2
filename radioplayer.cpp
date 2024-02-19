#include "radioplayer.h"
#include <QDebug>
#include <QSettings>

RadioPlayer::RadioPlayer(QObject *parent)
    : QObject{parent}
{

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &RadioPlayer::metadata);
}

RadioPlayer::~RadioPlayer()
{
    delete timer;
    delete player;
    delete audiooutput;
    BASS_StreamFree(str);                   //освободить поток
    BASS_Free();
}

// ----------------------------- инициализация плеера ---------------------------------------

void RadioPlayer::init()
{
    BASS_Free();
    delete audiooutput;
    delete player;
    audiooutput = 0;
    player = 0;

    if(library=="BASS")
    {
        BASS_Init (-1, 44100, 0 , 0, 0);
        BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST, 1);
    }
    if(library=="QMediaPlayer")
    {
        player = new QMediaPlayer(this);
        audiooutput = new QAudioOutput();
        player->setAudioOutput(audiooutput);
    }
}

// ----------------------------- запустить воспроизведение ----------------------------------

void RadioPlayer::play()
{
    timer->stop();

    if(library=="BASS")
    {
        BASS_ChannelPlay(str, 0);
    }
    if(library=="QMediaPlayer")
    {
        player->setSource(url_radio);
        player->play();
    }
    timer->start(50);
}

// ------------------------------- остановить воспроизведение --------------------------------

void RadioPlayer::stop()
{
    if(library=="BASS")
    {
        BASS_ChannelStop(str);
    }
    if(library=="QMediaPlayer")
    {
        player->stop();
    }
    timer->stop();
}

// ----------------------------- читаем метаданные из потока ----------------------------------

void RadioPlayer::metadata()
{
    if(library=="BASS")
    {
        const char *comments = BASS_ChannelGetTags(str, BASS_TAG_META);
        if (comments)
        {
            const char *s = strstr(comments, "StreamTitle='");
            if (s) {
                const char *f = strstr(s, "';");
                if (f) {
                    char *track_name = strdup(s + 13);
                    track_name[f - (s + 13)] = 0;
                    emit track_signal(track_name);
                }
            }
        }
    }
    if(library=="QMediaPlayer")
    {
        track_name = player->metaData().value(QMediaMetaData::Title).toString();
        emit track_signal(track_name);
    }
}

// -------------------- включить поток радио по заданному url -----------------------------------

void RadioPlayer::play_radio(QString url)
{
    url_radio = url;
    timer->stop();
    if(library=="BASS")
    {
        BASS_ChannelStop(str);//остановить проигрывание
        BASS_StreamFree(str);//освободить поток
        str=BASS_StreamCreateURL(url_radio.toStdString().c_str(), 0, 0, NULL, 0);     // загрузка в поток                                                    // проигрывание потока
    }
    if(library=="QMediaplayer")
    {
        player->setSource(url_radio);
    }
    play();
    timer->start(50);
}

// --------------------- устанавливаем значение library ----------------------------------------

void RadioPlayer::set_library(QString lib)
{
    library = lib;
    init();
    timer->stop();
}
