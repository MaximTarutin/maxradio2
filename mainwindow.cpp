#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    trayIcon =        new QSystemTrayIcon(this);
    database =        new DataBaseRadio();
    exit_action =     new QAction(this);
    playlist_action = new QAction(this);

    database->open_database();                      // Открываем базу данных
    database->init_database();                      // Инициируем таблицы



    qDebug() << database->proba();
    init();

}

MainWindow::~MainWindow()
{
    delete playlist_action;
    delete exit_action;
    delete database;
    delete trayIcon;

}

// ------------------------ Инициализация программы ---------------------------

void MainWindow::init()
{
    QIcon trayImage(":/res/radio-gray.png");                   // Приложение запускаем в трее
    trayIcon->setIcon(trayImage);
    trayIcon->show();

}
