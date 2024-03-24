#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private:
    Ui::AboutWindow *ui;
    QLabel          *background;

private slots:
    void close_window();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

};

#endif // ABOUTWINDOW_H
