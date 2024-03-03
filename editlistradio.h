#ifndef EDITLISTRADIO_H
#define EDITLISTRADIO_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>

namespace Ui {
class EditlistRadio;
}

class EditlistRadio : public QWidget
{
    Q_OBJECT

public:
    explicit EditlistRadio(QWidget *parent = nullptr);
    ~EditlistRadio();
    void get_name_radio(std::list <QString> r);     // получаем список названия радиостанций
    void get_group_radio(std::list <QString> r);    // получаем список групп радиостанций
    void init();                                    // инициализация

private:
    Ui::EditlistRadio   *ui;
    QLabel              *background;                // фон редактора;
    std::list <QString>  nameRadio;                 // список радиостанций
    std::list <QString>  groupsRadio;               // список групп радиостанций
    QMessageBox         *message;                   // всплывающие окна

private slots:
    void close_editor();                            // закрыть окно редактора
    void changed_groups();                          // Обновляем del_combobox с названиями радиостанций
    void check_delete();                            // Проверка на возможность удаления радио из бд

signals:
    void reset_playlist();                          // сигнал сбросить плейлист ловится в mainwindow.cpp
    void delete_yes(QString nameRadio);             // сигнал удалить радиостанцию ловится в mainwindow.cpp
};

#endif // EDITLISTRADIO_H
