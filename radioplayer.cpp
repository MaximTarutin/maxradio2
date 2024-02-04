#include "radioplayer.h"
#include <QDebug>

RadioPlayer::RadioPlayer()
{
    audiooutput = new QAudioOutput;
    this->setAudioOutput(audiooutput);

    connect(this, &RadioPlayer::positionChanged,
            this, [this](){emit play_track(this->metaData().value(QMediaMetaData::Title).toString());});
}

RadioPlayer::~RadioPlayer()
{
    delete audiooutput;
}

void RadioPlayer::play_radio(QString url)
{
    this->setSource(url);
    this->play();
    track_name=this->metaData().value(QMediaMetaData::Title).toString();
    qDebug() << track_name;
}
