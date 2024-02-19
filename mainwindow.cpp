#include "mainwindow.h"
#include <QDebug>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    trayIcon =        new QSystemTrayIcon(this);
    database =        new DataBaseRadio();
    menu =            new QMenu(this);
    submenu =         new QMenu("Выбор библиотеки", menu);
    qt_library =      new QAction("библиотека Qt", submenu);
    bass_library =    new QAction("библиотека BASS", submenu);
    exit_action =     new QAction("Выход", this);
    editor_action =   new QAction("Редактор радиостанций", this);
    playlist_window = new PlaylistRadio();
    radio =           new RadioPlayer();

    nameRadio = "";

    library = get_settings();                           // читаем настройки программы

    if(library!="BASS" and library!="QMediaPlayer")
    {
        if(OS=="Linux")
        {
            qt_library->setIcon(QIcon(":/res/galka.png"));
            bass_library->setIcon(QIcon(":/res/prosrach.png"));
            radio->set_library("QMediaPlayer");
            set_settings("QMediaPlayer");
            library = "QMediaPlayer";
        }
        if(OS=="Windows")
        {
            bass_library->setIcon(QIcon(":/res/galka.png"));
            qt_library->setIcon(QIcon(":/res/prosrach.png"));
            radio->set_library("BASS");
            set_settings("BASS");
            library = "BASS";
        }
    } else
    {
        if(library=="BASS")
        {
            bass_library->setIcon(QIcon(":/res/galka.png"));
            qt_library->setIcon(QIcon(":/res/prosrach.png"));
            radio->set_library("BASS");
        }
        if(library=="QMediaPlayer")
        {
            qt_library->setIcon(QIcon(":/res/galka.png"));
            bass_library->setIcon(QIcon(":/res/prosrach.png"));
            radio->set_library("QMediaPlayer");
        }
    }

    database->open_database();                      // Открываем базу данных
    database->init_database();                      // Инициируем таблицы

    init();
    playlist_window->get_groups_radio(database->read_groups_db());  // читаем данные из базы данных
    playlist_window->get_name_radio(database->read_name_db());      // и формируем плейлист
    playlist_window->get_url_radio(database->read_url_db());

    playlist_window->init();

    connect(exit_action,     &QAction::triggered,               this,   &MainWindow::exit_of_programm);     // выход из программы
    connect(trayIcon,        &QSystemTrayIcon::activated,       this,   &MainWindow::show_list_radio);      // клик по иконке
    connect(playlist_window, &PlaylistRadio::name_signal,       this,   &MainWindow::get_url_radio);        // получаем название выбранного радио
    //connect(radio, &RadioPlayer::positionChanged, this, &MainWindow::iconChanged);                        // меняем цвет иконки
    connect(playlist_window, &PlaylistRadio::play_stop_signal,  this,   &MainWindow::play_stop);            // нажатие кнопок в плейлисте
    connect(radio,           &RadioPlayer::track_signal,        this,   &MainWindow::get_track_name);       // ловим название трека
    connect(bass_library,    &QAction::triggered,               this,   &MainWindow::switch_lib_BASS);      // переключаемся на BASS
    connect(qt_library,      &QAction::triggered,               this,   &MainWindow::switch_lib_Qt);        // переключаемся на Qt
    connect(editor_action,   &QAction::triggered,               this,   &MainWindow::editor);
}

MainWindow::~MainWindow()
{
    delete radio;
    delete playlist_window;
    delete editor_action;
    delete exit_action;
    delete bass_library;
    delete qt_library;
    delete submenu;
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
    menu->addMenu(submenu);                                      // выбор используемой библиотеки QMedia или BASS
    submenu->addAction(qt_library);
    submenu->addAction(bass_library);
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
    qDebug() << library;
    radio->init();
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
        //QIcon trayImage(":/res/radio-color.png");
        //trayIcon->setIcon(trayImage);
    }
    else
    {
        radio->stop();
        //QIcon trayImage(":/res/radio-gray.png");
        //trayIcon->setIcon(trayImage);
    }
}

// ---------------------- Показываем текущую композицию ---------------------------

void MainWindow::track_name(QString name)
{
    playlist_window->show_track_label(name);
    name=nameRadio+"\n"+name;
    trayIcon->setToolTip(name);    
}

// --------------------------- Переключаем библиотеку на BASS  ---------------------

void MainWindow::switch_lib_BASS()
{
    QString lib = get_settings();
    if(lib=="BASS") return;
    set_settings("BASS");
    library = "BASS";
    radio->set_library("BASS");
    bass_library->setIcon(QIcon(":/res/galka.png"));
    qt_library->setIcon(QIcon(":/res/prosrach.png"));
}

// -------------------------- Переключаем библиотеку на QMediaPlayer ----------------

void MainWindow::switch_lib_Qt()
{
    QString lib = get_settings();
    if(lib=="QMediaPlayer") return;
    set_settings("QMediaPlayer");
    library = "QMediaPlayer";
    radio->set_library("QMediaPlayer");
    qt_library->setIcon(QIcon(":/res/galka.png"));
    bass_library->setIcon(QIcon(":/res/prosrach.png"));
}

// ------------------------------ Редактор радиостанций ------------------------------

void MainWindow::editor()
{

}

// ------------------------------ Читаем настройки программы ---------------------------

QString MainWindow::get_settings()
{
    settings = new QSettings();
    QString lib = settings->value("library").toString();
    delete settings;
    settings = 0;
    return lib;
}

// ----------------- Записываем в настройки какая библиотека используется ---------------

void MainWindow::set_settings(QString name)
{
    settings = new QSettings();
    settings->setValue("library", name);
    delete settings;
    settings = 0;
}

// ----------------------- ловим сигнал с названием песни ------------------------------

void MainWindow::get_track_name(QString name)
{
    trayIcon->setToolTip(nameRadio+"\n"+name);
    playlist_window->show_track_label(name);
}
