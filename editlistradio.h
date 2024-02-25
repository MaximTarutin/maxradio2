#ifndef EDITLISTRADIO_H
#define EDITLISTRADIO_H

#include <QWidget>
#include <QLabel>


namespace Ui {
class EditlistRadio;
}

class EditlistRadio : public QWidget
{
    Q_OBJECT

public:
    explicit EditlistRadio(QWidget *parent = nullptr);
    ~EditlistRadio();

private:
    Ui::EditlistRadio   *ui;
    QLabel              *background;                // фон редактора;

private slots:
    void close_editor();                            // закрыть окно редактора
    void init();                                    // инициализация

signals:
    void reset_playlist();

};

#endif // EDITLISTRADIO_H
