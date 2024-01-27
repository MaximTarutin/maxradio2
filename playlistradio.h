#ifndef PLAYLISTRADIO_H
#define PLAYLISTRADIO_H

#include <QWidget>
#include <QLabel>

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
    std::list <QString> put_groups_radio();         // передаем список радиостанций
    void get_name_radio(std::list <QString> r);     // получаем список групп радиостанций
    std::list <QString> put_name_radio();           // передаем список радиостанций
    void get_url_radio(std::list <QString> r);      // получаем список групп радиостанций
    std::list <QString> put_url_radio();           // передаем список радиостанций

private:
    Ui::PlaylistRadio *ui;

    QLabel              *background;        // фоновая картинка плейлиста
    QLabel              *runstring;         // бегущая строка
    std::list <QString>  groupsRadio;       // список групп радиостанций
    std::list <QString>  nameRadio;         // список радиостанций
    std::list <QString>  urlRadio;          // список url радиостанций

};

#endif // PLAYLISTRADIO_H
