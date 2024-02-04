#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QScreen>
#include <QString>
#include "databaseradio.h"
#include "playlistradio.h"
#include "radioplayer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString nameRadio;

private:
    QSystemTrayIcon     *trayIcon;                  // иконка трее
    DataBaseRadio       *database;                  // база данных
    QMenu               *menu;                      // контекстное меню
    QAction             *exit_action;               // пункт меню выход из программы
    QAction             *editor_action;             // пункт меню открыть плейлист
    PlaylistRadio       *playlist_window;           // окно плейлиста
    QScreen             *screen;
    RadioPlayer         *radio;                     // плеер радио
    int                 size_w;                     // ширина экрана
    int                 size_h;                     // высота экрана
    bool                FLAG_SHOW;                  // видимость playlist_window


private slots:
    void init();                                                // инициализация программы
    void exit_of_programm();                                    // выход из программы
    void show_list_radio(QSystemTrayIcon::ActivationReason);    // Показать список радиостанций
    void init_size();                                           // Инициализация переменных size_w, size_h
    void get_url_radio(QString name);                           // получаем url выбранного радио из базы данных
    void iconChanged(bool v);                                   // меняем цвет иконки в зависимости от состояния радио
    void play_stop(bool v);                                     // нажатие кнопок в плейлисте
    void track_name(QString name);                              // Показываем текущую композицию
};

#endif // MAINWINDOW_H
