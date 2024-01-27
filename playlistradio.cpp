#include "playlistradio.h"
#include "ui_playlistradio.h"
#include <QDebug>

PlaylistRadio::PlaylistRadio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistRadio)
{
    ui->setupUi(this);

    background =        new QLabel(this);               // Фон
    runstring =         new QLabel(ui->track_label);    // Бегущая строка

    background->resize(this->width(), this->height());
    background->lower();
    background->setStyleSheet("background-color: rgba(255, 255, 255, 0); border-image: url(:/res/ramka.png);");
    runstring->move(190, 5);
    runstring->resize(600, 30);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::Popup);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setAttribute(Qt::WA_TranslucentBackground);                       // делаем окно прозрачным

    this->ui->Button_play->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                         "border-image: url(:/res/play.png);");
    this->ui->Button_stop->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                         "border-image: url(:/res/stop-d.png);");
}

PlaylistRadio::~PlaylistRadio()
{
    delete runstring;
    delete background;
}

