#ifndef RADIOPLAYER_H
#define RADIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>

class RadioPlayer: public QMediaPlayer
{
    Q_OBJECT
public:
    RadioPlayer();
    ~RadioPlayer();

    QAudioOutput    *audiooutput;

public:
    void play_radio(QString url);

private:
    QString     track_name;             // Название текущей композиции

signals:
    void play_track(QString);           // Сигнал передающий название трека
};

#endif // RADIOPLAYER_H
