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

extern QString      OS;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString nameRadio;


private:
    QSystemTrayIcon     *trayIcon = 0;                  // иконка трее
    DataBaseRadio       *database = 0;                  // база данных
    QMenu               *menu = 0;                      // контекстное меню
    QMenu               *submenu = 0;                   // подменю выбора какую библиотеку использовать
    QAction             *qt_library = 0;                // библиотека QMediaPlayer
    QAction             *bass_library = 0;              // библиотека BASS
    QAction             *exit_action = 0;               // пункт меню выход из программы
    QAction             *editor_action = 0;             // пункт меню открыть плейлист
    PlaylistRadio       *playlist_window = 0;           // окно плейлиста
    QScreen             *screen = 0;
    RadioPlayer         *radio = 0;                     // плеер радио
    QSettings           *settings = 0;                  // настройки программы
    int                 size_w;                         // ширина экрана
    int                 size_h;                         // высота экрана
    bool                FLAG_SHOW;                      // видимость playlist_window
    QString             library;                        // используемая библиотека BASS or QMediaPlayer
    EditlistRadio       *editor_window = 0;             // редактор плейлиста
    QMessageBox         *message = 0;                   // всплывающие окна

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
};

#endif // MAINWINDOW_H
