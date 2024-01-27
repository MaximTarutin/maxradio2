#include "mainwindow.h"
#include <QDebug>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    FLAG_SHOW = false;

    trayIcon =        new QSystemTrayIcon(this);
    database =        new DataBaseRadio();
    menu =            new QMenu(this);
    exit_action =     new QAction("Выход", this);
    editor_action =   new QAction("Редактор радиостанций", this);
    playlist_window = new PlaylistRadio();

    database->open_database();                      // Открываем базу данных
    database->init_database();                      // Инициируем таблицы



    qDebug() << database->proba();
    init();

    connect(exit_action,    &QAction::triggered,            this,   &MainWindow::exit_of_programm);     // выход из программы
    connect(trayIcon,       &QSystemTrayIcon::activated,    this,   &MainWindow::show_list_radio);      // клик по иконке

}

MainWindow::~MainWindow()
{
    delete editor_action;
    delete exit_action;
    delete menu;
    delete database;
    delete trayIcon;

}

// ------------------------ Инициализация программы ---------------------------

void MainWindow::init()
{
    QIcon trayImage(":/res/radio-gray.png");                    // Приложение запускаем в трее
    trayIcon->setIcon(trayImage);
    trayIcon->show();
    menu->addAction(editor_action);                              // Формируем меню приложения
    menu->addSeparator();
    menu->addAction(exit_action);
    trayIcon->setContextMenu(menu);
}

// ---------------------------- Выход из программы ----------------------------

void MainWindow::exit_of_programm()
{
    exit(0);
}

// ----------------------------- Инициализация переменных size_w, size_h -----------------------------

void MainWindow::init_size()
{
    screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    size_w = size.width();                                      // Ширина экрана
    size_h = size.height();                                     // Высота экрана
}

// ----------------------------- Список радиостанций ----------------------------------

void MainWindow::show_list_radio(QSystemTrayIcon::ActivationReason r)
{
    if (!FLAG_SHOW)
    {
        if (r==QSystemTrayIcon::Trigger)
        {
            int x_cur, y_cur;
            x_cur = QCursor::pos().x();
            y_cur = QCursor::pos().y();

            if(y_cur < size_h/2)
            {
                playlist_window->move(x_cur-playlist_window->width()/2, y_cur+40);
            } else
            {
                playlist_window->move(x_cur-playlist_window->width()/2, y_cur-playlist_window->height()-40);
            }
            playlist_window->show();
        }
        FLAG_SHOW = true;
        return;
    } else
    {
        playlist_window->hide();
        FLAG_SHOW = false;
        return;
    }
}

