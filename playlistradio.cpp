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
    runstring->setStyleSheet(QString("font-size: %1px").arg(20));
    runstring->show();

    background->resize(this->width(), this->height());
    background->lower();
    background->setStyleSheet("background-color: rgba(255, 255, 255, 0); border-image: url(:/res/ramka.png);");
    runstring->move(190, 5);
    runstring->resize(600, 30);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::Popup);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setAttribute(Qt::WA_TranslucentBackground);                       // делаем окно прозрачным

    this->ui->verticalSlider->setValue(50);

    this->ui->Button_play->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                         "border-image: url(:/res/play.png);");
    this->ui->Button_stop->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                         "border-image: url(:/res/stop-d.png);");


    connect(ui->verticalSlider, &QSlider::sliderMoved,      this, &PlaylistRadio::position_slider);
    connect(ui->verticalSlider, &QSlider::sliderPressed,    this, &PlaylistRadio::position_slider);
    connect(ui->verticalSlider, &QSlider::sliderReleased,   this, &PlaylistRadio::position_slider);

    connect(ui->comboBox_classic, &QComboBox::currentTextChanged, this,             // отправляем сигналы с названием радио
            [this]() {show_name_radio(ui->comboBox_classic->currentText());});      // и отображаем название радиостанции
    connect(ui->comboBox_dance, &QComboBox::currentTextChanged,this,
            [this]() {show_name_radio(ui->comboBox_dance->currentText());});
    connect(ui->comboBox_hiphop, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_hiphop->currentText());});
    connect(ui->comboBox_humor, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_humor->currentText());});
    connect(ui->comboBox_kind, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_kind->currentText());});
    connect(ui->comboBox_news, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_news->currentText());});
    connect(ui->comboBox_other, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_other->currentText());});
    connect(ui->comboBox_pop, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_pop->currentText());});
    connect(ui->comboBox_rok, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_rok->currentText());});
    connect(ui->comboBox_shanson, &QComboBox::currentTextChanged, this,
            [this]() {show_name_radio(ui->comboBox_shanson->currentText());});
    connect(ui->Button_play, &QPushButton::clicked, this, [this] ()                         // нажата кнопка play
            {
                emit play_stop_signal(true);
                ui->Button_play->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                             "border-image: url(:/res/play.png);");
                ui->Button_stop->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                             "border-image: url(:/res/stop-d.png);");
            });
    connect(ui->Button_stop, &QPushButton::clicked, this, [this] ()                         // нажата кнопка stop
            {
                emit play_stop_signal(false);
                ui->Button_play->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                            "border-image: url(:/res/play-d.png);");
                ui->Button_stop->setStyleSheet("background-color: rgba(255, 255, 255, 0); "
                                            "border-image: url(:/res/stop.png);");
            });
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

    ui->comboBox_humor->clear();    ui->comboBox_humor->addItem("Юмор");
    ui->comboBox_rok->clear();      ui->comboBox_rok->addItem("Рок");
    ui->comboBox_pop->clear();      ui->comboBox_pop->addItem("Поп");
    ui->comboBox_other->clear();    ui->comboBox_other->addItem("Другое");
    ui->comboBox_news->clear();     ui->comboBox_news->addItem("Новости");
    ui->comboBox_shanson->clear();  ui->comboBox_shanson->addItem("Шансон");
    ui->comboBox_classic->clear();  ui->comboBox_classic->addItem("Классика");
    ui->comboBox_hiphop->clear();   ui->comboBox_hiphop->addItem("Реп, хип-хоп");
    ui->comboBox_dance->clear();    ui->comboBox_dance->addItem("Танцевальная");
    ui->comboBox_kind->clear();     ui->comboBox_kind->addItem("Детское");

    // Проходимся по двум спискам одновременно и заполняем плейлист

    for(std::list<QString>::iterator it1=groupsRadio.begin(), it2=nameRadio.begin();
         (it1!=groupsRadio.end())&&(it2!=nameRadio.end());
         ++it1, ++it2)
    {
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

// --------------- Показываем название выбранной радиостанции в radio_label ------------------

void PlaylistRadio::show_name_radio(QString name)
{
    if(name!="Рок" and name!="Поп" and name!="Классика" and name!="Детское" and
       name!="Танцевальная" and name!="Реп, хип-хоп" and name!="Шансон" and
       name!="Новости" and name!="Юмор" and name!="Другое")
    {
        emit name_signal(name);
        ui->radio_label->setText(name);
    }
    ui->comboBox_classic->setCurrentIndex(0);
    ui->comboBox_dance->setCurrentIndex(0);
    ui->comboBox_hiphop->setCurrentIndex(0);
    ui->comboBox_humor->setCurrentIndex(0);
    ui->comboBox_kind->setCurrentIndex(0);
    ui->comboBox_news->setCurrentIndex(0);
    ui->comboBox_other->setCurrentIndex(0);
    ui->comboBox_pop->setCurrentIndex(0);
    ui->comboBox_rok->setCurrentIndex(0);
    ui->comboBox_shanson->setCurrentIndex(0);
}

// ------------------ Показываем название текущего трека -----------------------------------

void PlaylistRadio::show_track_label(QString name)
{
    static int count;
    count=count-3;
    runstring->setText(name);
    if (count <= -240) count = 240;
    runstring->move(count, 5);
}

// ------------------------- Регулировка громкости посылаем сигнал ----------------

void PlaylistRadio::wheelEvent(QWheelEvent *event)
{
    float x;
    x = this->ui->verticalSlider->value();
    QPoint angle = event->angleDelta()/8;
    event->accept();

    if(angle.y() > 0)                               // Добавляем громкость
    {
        x=x+2;
        if(x>100) x=100;
        this->ui->verticalSlider->setValue(x);
        emit volume(x);
    } else                                          // Убавляем громкость
    {
        x=x-2;
        if(x<0) x=0;
        this->ui->verticalSlider->setValue(x);
        emit volume(x);
    }
}

// ---------------- считываем позицию слайдера и передаём сигнал volume -------------

void PlaylistRadio::position_slider()
{
    emit volume(this->ui->verticalSlider->value());
}
