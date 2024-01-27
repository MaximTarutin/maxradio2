#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    trayIcon =  new QSystemTrayIcon(this);
    database =  new Maxradio_DataBase(this);

    database->open_database();                      // Открываем базу данных
    database->init_database();                      // Инициируем таблицы
    init();

}

MainWindow::~MainWindow()
{
    delete trayIcon;
    delete database;
}

// ------------------------ Инициализация программы ---------------------------

void MainWindow::init()
{
    QIcon trayImage(":/res/radio-gray.png");                   // Приложение запускаем в трее
    trayIcon->setIcon(trayImage);
    trayIcon->show();

}
