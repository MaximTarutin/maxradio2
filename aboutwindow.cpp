#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    background =    new QLabel(this);

    background->resize(this->width(), this->height());
    background->lower();
    background->setStyleSheet("background-color: rgba(255, 255, 255, 0); border-image: url(:/res/frames.png); ");
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);                       // делаем окно прозрачным

    connect(ui->closeButton,    &QPushButton::clicked,  this,   &AboutWindow::close_window);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::close_window()
{
    this->close();
}

void AboutWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key==Qt::Key_Escape)
    {
        this->close();
    }
}
