#ifndef RADIOPLAYER_H
#define RADIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class RadioPlayer: public QMediaPlayer
{
    Q_OBJECT
public:
    RadioPlayer();
    ~RadioPlayer();

    QAudioOutput    *audiooutput;

public:
    void play_radio(QString url);
};

#endif // RADIOPLAYER_H
