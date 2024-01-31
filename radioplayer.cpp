#include "radioplayer.h"

RadioPlayer::RadioPlayer()
{
    audiooutput = new QAudioOutput;
    this->setAudioOutput(audiooutput);
}

RadioPlayer::~RadioPlayer()
{
    delete audiooutput;
}

void RadioPlayer::play_radio(QString url)
{
    this->setSource(url);
    this->play();
}
