#include "mainwindow.h"
#include <QDebug>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    trayIcon =        new QSystemTrayIcon(this);
    database =        new DataBaseRadio();
    menu =            new QMenu(this);
    exit_action =     new QAction("Выход", this);
    editor_action =   new QAction("Редактор радиостанций", this);
    playlist_window = new PlaylistRadio();
    radio =           new RadioPlayer();
    nameRadio = "";

    database->open_database();                      // Открываем базу данных
    database->init_database();                      // Инициируем таблицы

    init();
    playlist_window->get_groups_radio(database->read_groups_db());  // читаем данные из базы данных
    playlist_window->get_name_radio(database->read_name_db());      // и формируем плейлист
    playlist_window->get_url_radio(database->read_url_db());

    playlist_window->init();

    connect(exit_action,    &QAction::triggered,            this,   &MainWindow::exit_of_programm);     // выход из программы
    connect(trayIcon,       &QSystemTrayIcon::activated,    this,   &MainWindow::show_list_radio);      // клик по иконке
    connect(playlist_window, &PlaylistRadio::name_signal,   this,   &MainWindow::get_url_radio);        // получаем название выбранного радио
    connect(radio, &RadioPlayer::positionChanged, this, &MainWindow::iconChanged);                      // меняем цвет иконки
    connect(playlist_window, &PlaylistRadio::play_stop_signal, this, &MainWindow::play_stop);           // нажатие кнопок в плейлисте
    connect(radio,  &RadioPlayer::play_track,   this,   &MainWindow::track_name);                       // ловим название трека
}

MainWindow::~MainWindow()
{
    delete radio;
    delete playlist_window;
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

// ----------------------------- Показываем окно плейлиста ----------------------------------

void MainWindow::show_list_radio(QSystemTrayIcon::ActivationReason r)
{
    if (r==QSystemTrayIcon::Trigger)            // расположение окна плейлиста в зависимости от
    {                                           // расположения панели
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
}

// ------------------------ Получаем url радио и воспроизводим его -----------------------------------

void MainWindow::get_url_radio(QString name)
{
    QString url = database->get_url_radio(name);
    if (url=="") return;
    radio->play_radio(url);
    nameRadio = name;
}

// -------------------------------- Меняем цвет иконки -----------------------------------------------

void MainWindow::iconChanged(bool v)
{
    if(v)
    {
        QIcon trayImage(":/res/radio-color.png");
        trayIcon->setIcon(trayImage);
    } else
    {
        QIcon trayImage(":/res/radio-gray.png");
        trayIcon->setIcon(trayImage);
    }
    trayIcon->show();
}

// --------------- нажатие кнопок play и stop в окне плейлиста -------------------

void MainWindow::play_stop(bool v)
{
    if(v)
    {
        radio->play();
        QIcon trayImage(":/res/radio-color.png");
        trayIcon->setIcon(trayImage);
    }
    else
    {
        radio->stop();
        QIcon trayImage(":/res/radio-gray.png");
        trayIcon->setIcon(trayImage);
    }
}

// ---------------------- Показываем текущую композицию ---------------------------

void MainWindow::track_name(QString name)
{
    playlist_window->show_track_label(name);
    name=nameRadio+"\n"+name;
    trayIcon->setToolTip(name);    
}
