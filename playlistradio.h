#ifndef PLAYLISTRADIO_H
#define PLAYLISTRADIO_H

#include <QWidget>
#include <QLabel>
#include <map>

namespace Ui {
class PlaylistRadio;
}

class PlaylistRadio : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistRadio(QWidget *parent = nullptr);
    ~PlaylistRadio();

    void get_groups_radio(std::list <QString> r);   // получаем список групп радиостанций
    void get_name_radio(std::list <QString> r);     // получаем список групп радиостанций
    void get_url_radio(std::list <QString> r);      // получаем список групп радиостанций
    void init();

private:
    Ui::PlaylistRadio *ui;

    QLabel              *background;                // фоновая картинка плейлиста
    QLabel              *runstring;                 // бегущая строка
    std::list <QString>  groupsRadio;               // список групп радиостанций
    std::list <QString>  nameRadio;                 // список радиостанций
    std::list <QString>  urlRadio;                  // список url радиостанций

signals:
    void name_signal(QString);                      // Сигнал передает название радио
    void play_stop_signal(bool);                    // true - нажата кнопка play, false - stop

};

#endif // PLAYLISTRADIO_H
