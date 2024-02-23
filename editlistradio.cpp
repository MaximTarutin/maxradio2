#include "editlistradio.h"
#include "ui_editlistradio.h"

EditlistRadio::EditlistRadio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditlistRadio)
{
    ui->setupUi(this);

    init();

    connect(ui->return_pushButton,  &QPushButton::clicked,  this,   &EditlistRadio::close_editor);  // закрываем окно

}

EditlistRadio::~EditlistRadio()
{
    delete ui;
}

// ---------------------------- инициализация -------------------------------------

void EditlistRadio::init()
{
    background      = new QLabel(this);

    background->resize(this->width(), this->height());
    background->lower();
    background->setStyleSheet("background-color: rgba(255, 255, 255, 0); border-image: url(:/res/vborder.png); ");

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);                       // делаем окно прозрачным
}

// --------------------------- закрыть окно редактора -----------------------------

void EditlistRadio::close_editor()
{
    this->close();
}



