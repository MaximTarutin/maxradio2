#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include "databaseradio.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSystemTrayIcon     *trayIcon;                  // иконка трее
    DataBaseRadio       *database;                  // база данных
    QMenu               *menu;                      // контекстное меню
    QAction             *exit_action;               // пункт меню выход из программы
    QAction             *playlist_action;           // пункт меню открыть плейлист


private slots:
    void init();                        // инициализация программы
    void exit_of_programm();            // выход из программы
};

#endif // MAINWINDOW_H
