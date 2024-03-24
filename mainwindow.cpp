#include "mainwindow.h"
//#include <QDebug>
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
    about_action  =   new QAction("О программе", this);
    playlist_window = new PlaylistRadio();
    radio =           new RadioPlayer();
    editor_window =   new EditlistRadio();
    message =         new QMessageBox(editor_window);
    about_window =    new AboutWindow();

    nameRadio = "";

    library = get_settings();                           // читаем настройки программы
    radio->set_volume(50);

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

    init_size();
    init();
    reload_editor_playlist();                       // формируем список радиостанций из базы данных в окнах редактора и плейлиста

    connect(exit_action,     &QAction::triggered,               this,   &MainWindow::exit_of_programm);         // выход из программы
    connect(trayIcon,        &QSystemTrayIcon::activated,       this,   &MainWindow::show_list_radio);          // клик по иконке
    connect(playlist_window, &PlaylistRadio::name_signal,       this,   &MainWindow::get_url_radio);            // получаем название выбранного радио
    connect(radio,           &RadioPlayer::isPlaying,           this,   &MainWindow::iconChanged);              // меняем цвет иконки
    connect(playlist_window, &PlaylistRadio::play_stop_signal,  this,   &MainWindow::play_stop);                // нажатие кнопок в плейлисте
    connect(radio,           &RadioPlayer::track_signal,        this,   &MainWindow::get_track_name);           // ловим название трека
    connect(bass_library,    &QAction::triggered,               this,   &MainWindow::switch_lib_BASS);          // переключаемся на BASS
    connect(qt_library,      &QAction::triggered,               this,   &MainWindow::switch_lib_Qt);            // переключаемся на Qt
    connect(editor_action,   &QAction::triggered,               this,   &MainWindow::editor);                   // редактор плейлиста
    connect(playlist_window, &PlaylistRadio::volume,            this,   &MainWindow::set_volume);               // ловим уровень громкости
    connect(editor_window,   &EditlistRadio::reset_playlist,    this,   &MainWindow::reset_playlist);           // сброс плейлиста
    connect(editor_window,   &EditlistRadio::delete_yes,        this,   &MainWindow::delete_radio);             // удаляем радиостанцию
    connect(editor_window,   &EditlistRadio::add_radio,         this,   &MainWindow::add_radio);                // добавляем радиостанцию
    connect(about_action,    &QAction::triggered,               this,   &MainWindow::about);
}

MainWindow::~MainWindow()
{
    delete about_window;
    delete about_action;
    delete message;
    delete editor_window;
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
    menu->addAction(about_action);
    menu->addSeparator();
    menu->addAction(exit_action);
    trayIcon->setContextMenu(menu);
}

// ----------------------------- Инициализация переменных size_w, size_h -----------------------------

void MainWindow::init_size()
{
    screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    size_w = size.width();                                      // Ширина экрана
    size_h = size.height();                                     // Высота экрана
}

// ------------------------------ Читаем настройки программы ---------------------------

QString MainWindow::get_settings()
{
    settings = new QSettings();
    QString lib = settings->value("library").toString();
    radio->set_library(lib);
    delete settings;
    settings = 0;
    return lib;
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
    QIcon trayImage(":/res/radio-gray.png");
    trayIcon->setIcon(trayImage);
    trayIcon->show();
    playlist_window->show_track_label("");
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
    QIcon trayImage(":/res/radio-gray.png");
    trayIcon->setIcon(trayImage);
    trayIcon->show();
    playlist_window->show_track_label("");

}

// ----------------- Записываем в настройки какая библиотека используется ---------------

void MainWindow::set_settings(QString name)
{
    settings = new QSettings();
    settings->setValue("library", name);
    delete settings;
    settings = 0;
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

// ----------------------- ловим сигнал с названием песни ------------------------------

void MainWindow::get_track_name(QString name)
{
    trayIcon->setToolTip(nameRadio+"\n"+name);
    playlist_window->show_track_label(name);
}

// ---------------------- ловим сигнал уровня громкости ---------------------------------

void MainWindow::set_volume(int level)
{
    radio->set_volume(level);
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
    radio->init();
    radio->play_radio(url);
    nameRadio = name;
}

// --------------- нажатие кнопок play и stop в окне плейлиста -------------------

void MainWindow::play_stop(bool v)
{
    if(v)
    {
        radio->play();
    }
    else
    {
        radio->stop();
    }
}

// ---------------------- Показываем текущую композицию ---------------------------

void MainWindow::track_name(QString name)
{
    playlist_window->show_track_label(name);
    name=nameRadio+"\n"+name;
    trayIcon->setToolTip(name);
}

// ----------------- показываем окно редактора радиостанций ------------------https://horus.more.tv/v1/events-----

void MainWindow::editor()
{
    editor_window->show();
}

// --------------- сброс плейлиста к первоначальному состоянию --------------------

void MainWindow::reset_playlist()
{
    message->setStyleSheet("background-color: lightblue; color: black; "
                           "font: 700 italic 14pt 'Times New Roman';");
    message->setText("<center><font color = 'red'>ВНИМАНИЕ !</center>");
    message->setInformativeText("<center> Вы действительно хотите сбросить плейлист "
                                "к первоначальному состоянию? </center>");
    message->setIcon(QMessageBox::Warning);
    message->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    message->setWindowFlag(Qt::FramelessWindowHint);

    message->show();

    int ret = message->exec();

    switch (ret)
    {
    case QMessageBox::Cancel:
    {
        return;
    } break;
    case QMessageBox::Ok:
    {
        database->reset_database();             // удаляем таблицу из базы данных
        database->init_database();
        reload_editor_playlist();
    } break;
    }

}

// ---------------------------- Удаляем радиостанцию из плейлиста ------------------------------

void MainWindow::delete_radio(QString nameRadio)
{
    database->delete_radio(nameRadio);
    reload_editor_playlist();
}

// ---------------------------- Добавляем радиостанцию в плейлист -------------------------------

void MainWindow::add_radio(QString group, QString name, QString url)
{
    database->add_radio(group, name, url);
    reload_editor_playlist();
}

// --------------------------- Переинициализация списка радиостанций ---------------------------

void MainWindow::reload_editor_playlist()
{
    playlist_window->get_groups_radio(database->read_groups_db());
    playlist_window->get_name_radio(database->read_name_db());
    playlist_window->get_url_radio(database->read_url_db());
    playlist_window->init();

    editor_window->get_name_radio(database->read_name_db());
    editor_window->get_group_radio(database->read_groups_db());
    editor_window->init();
}

// ----------------------------- О программе --------------------------------------

void MainWindow::about()
{
    about_window->show();
}

// ---------------------------- Выход из программы --------------------------------

void MainWindow::exit_of_programm()
{
    exit(0);
}


