#include "radioplayer.h"
#include <QDebug>

RadioPlayer::RadioPlayer(QObject *parent)
    : QObject{parent}
{
    // BASS_PluginLoad("bass_aac", 0); // load BASS_AAC (if present) for AAC support
    // BASS_PluginLoad("bassflac", 0); // load BASSFLAC (if present) for FLAC support
    // BASS_PluginLoad("bassopus", 0); // load BASSOPUS (if present) for OPUS support
    // BASS_PluginLoad("basshls", 0); // load BASSHLS (if present) for HLS support

    BASS_Init (-1, 44100, 0 , 0, 0);
    BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST, 1);
    BASS_SetConfigPtr(BASS_CONFIG_LIBSSL, "libssl.so");

    //str = BASS_StreamCreateURL("",0,0,NULL,0);      // инициализируем пустой поток

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &RadioPlayer::metadata);
}

RadioPlayer::~RadioPlayer()
{
    delete timer;
    BASS_StreamFree(str);                   //освободить поток
    BASS_PluginFree(0);
}

void RadioPlayer::play()
{
    BASS_ChannelPlay(str, 0);                // проигрывание потока
    timer->start(1);
}

void RadioPlayer::stop()
{
    BASS_ChannelStop(str);                      //остановить проигрывание
    timer->stop();
}

void RadioPlayer::metadata()
{
    const char *comments = BASS_ChannelGetTags(str, BASS_TAG_META); // get a pointer to the 1st comment
    if(comments)
    {
        qDebug() << comments;
    }
}

void RadioPlayer::play_radio(QString url)
{
    BASS_ChannelStop(str);//остановить проигрывание
    BASS_StreamFree(str);//освободить поток
    str=BASS_StreamCreateURL(url.toStdString().c_str(), 0, 0, NULL, 0);         // загрузка в поток
    BASS_ChannelPlay(str, 0);                                                // проигрывание потока
    timer->start(1000);
}
