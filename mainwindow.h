#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QIcon>
#include "maxradio_database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSystemTrayIcon     *trayIcon;
    Maxradio_DataBase   *database;


private slots:
    void init();                        // инициализация программы
};

#endif // MAINWINDOW_H
