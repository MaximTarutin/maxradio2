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

private:
    Ui::PlaylistRadio *ui;

    QLabel              *background;        // фоновая картинка плейлиста
    QLabel              *runstring;         // бегущая строка



};

#endif // PLAYLISTRADIO_H
