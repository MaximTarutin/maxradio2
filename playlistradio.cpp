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

// ---------------------- Получаем список групп радиостанций и заносим в groupsRadio ---------------------------

void PlaylistRadio::get_groups_radio(std::list <QString> r)
{
    groupsRadio = r;
}

// ---------------------- Получаем список радиостанций и заносим в nameRadio ---------------------------

void PlaylistRadio::get_name_radio(std::list <QString> r)
{
    nameRadio = r;
}

// ---------------------- Получаем список url радиостанций и заносим в urlRadio ---------------------------

void PlaylistRadio::get_url_radio(std::list <QString> r)
{
    urlRadio = r;
}

// ------------------------- инициализация плейлиста ---------------------------------

void PlaylistRadio::init()
{
    // Очищаем списки

    ui->comboBox_rok->clear();      ui->comboBox_rok->addItem("Рок");
    ui->comboBox_pop->clear();      ui->comboBox_pop->addItem("Поп");
    ui->comboBox_other->clear();    ui->comboBox_other->addItem("Другое");
    ui->comboBox_news->clear();     ui->comboBox_news->addItem("Новости");
    ui->comboBox_shanson->clear();  ui->comboBox_shanson->addItem("Шансон");
    ui->comboBox_classic->clear();  ui->comboBox_classic->addItem("Классика");
    ui->comboBox_hiphop->clear();   ui->comboBox_hiphop->addItem("Реп, хип-хоп");
    ui->comboBox_dance->clear();    ui->comboBox_dance->addItem("Танцевальная");
    ui->comboBox_kind->clear();     ui->comboBox_kind->addItem("Детское");
    ui->comboBox_humor->clear();    ui->comboBox_humor->addItem("Юмор");

    // Проходимся по двум спискам одновременно и заполняем плейлист

    for(std::list<QString>::iterator it1=groupsRadio.begin(), it2=nameRadio.begin();
         (it1!=groupsRadio.end())&&(it2!=nameRadio.end());
         ++it1, ++it2)
    {
        qDebug() << *it1 << " : " << *it2;
        if (*it1=="Рок") this->ui->comboBox_rok->addItem(*it2);
        if (*it1=="Поп") this->ui->comboBox_pop->addItem(*it2);
        if (*it1=="Шансон") this->ui->comboBox_shanson->addItem(*it2);
        if (*it1=="Танцевальная") this->ui->comboBox_dance->addItem(*it2);
        if (*it1=="Реп, хип-хоп") this->ui->comboBox_hiphop->addItem(*it2);
        if (*it1=="Новости") this->ui->comboBox_news->addItem(*it2);
        if (*it1=="Юмор") this->ui->comboBox_humor->addItem(*it2);
        if (*it1=="Детское") this->ui->comboBox_kind->addItem(*it2);
        if (*it1=="Классика") this->ui->comboBox_classic->addItem(*it2);
        if (*it1=="Другое") this->ui->comboBox_other->addItem(*it2);
    }
}
