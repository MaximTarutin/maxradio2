#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QScreen>
#include <QString>
#include <QSettings>
#include <QProcess>
#include <QMessageBox>
#include "databaseradio.h"
#include "playlistradio.h"
#include "radioplayer.h"
#include "editlistradio.h"
#include "aboutwindow.h"

extern QString      OS;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString nameRadio;


private:
    QSystemTrayIcon     *trayIcon = nullptr;                  // иконка трее
    DataBaseRadio       *database = nullptr;                  // база данных
    QMenu               *menu = nullptr;                      // контекстное меню
    QMenu               *submenu = nullptr;                   // подменю выбора какую библиотеку использовать
    QAction             *pause_action = nullptr;              // пункт меню пауза
    QAction             *play_action = nullptr;               // пункт меню play
    QAction             *qt_library = nullptr;                // библиотека QMediaPlayer
    QAction             *bass_library = nullptr;              // библиотека BASS
    QAction             *exit_action = nullptr;               // пункт меню выход из программы
    QAction             *editor_action = nullptr;             // пункт меню открыть плейлист
    QAction             *about_action = nullptr;              // пункт меню о программе
    PlaylistRadio       *playlist_window = nullptr;           // окно плейлиста
    QScreen             *screen = nullptr;
    RadioPlayer         *radio = nullptr;                     // плеер радио
    QSettings           *settings = nullptr;                  // настройки программы
    int                 size_w;                               // ширина экрана
    int                 size_h;                               // высота экрана
    bool                FLAG_SHOW;                            // видимость playlist_window
    QString             library;                              // используемая библиотека BASS or QMediaPlayer
    EditlistRadio       *editor_window = nullptr;             // редактор плейлиста
    QMessageBox         *message = nullptr;                   // всплывающие окна
    AboutWindow         *about_window = nullptr;              // окно "О программе"

    void    reload_editor_playlist();                   // переинициализация списка радиостанций в окне
                                                        // редактора и плейлиста



private slots:
    void init();                                                // инициализация программы
    void exit_of_programm();                                    // выход из программы
    void show_list_radio(QSystemTrayIcon::ActivationReason);    // Показать список радиостанций
    void init_size();                                           // Инициализация переменных size_w, size_h
    void get_url_radio(QString name);                           // получаем url выбранного радио из базы данных
    void iconChanged(bool v);                                   // меняем цвет иконки в зависимости от состояния радио
    void play_stop(bool v);                                     // нажатие кнопок в плейлисте
    void track_name(QString name);                              // Показываем текущую композицию
    void switch_lib_BASS();                                     // переключаем библиотеку на BASS
    void switch_lib_Qt();                                       // переключаем библиотеку на Qt
    void editor();                                              // редактор радиостанций
    QString get_settings();                                     // читаем какая библиотека из настроек программы
    void set_settings(QString name);                            // изменяем в настройках библиотеку
    void get_track_name(QString name);                          // ловим сигнал с названием песни
    void set_volume(int level);                                 // ловим сигнал изменгения уровня громкости
    void reset_playlist();                                      // сброс плейлиста в начальное состояние
    void delete_radio(QString nameRadio);                       // удаляем радиостанцию из плейлиста
    void add_radio(QString group, QString name, QString url);   // добавляем радиостанцию в плейлист
    void about();
};

#endif // MAINWINDOW_H
