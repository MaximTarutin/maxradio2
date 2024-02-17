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

private slots:
    void metadata();                    // считываем метаданные

public:
    void play();                        // запуск потока
    void stop();                        // остановить поток
    void play_radio(QString url);       // запуск радио

signals:

};

#endif // RADIOPLAYER_H
