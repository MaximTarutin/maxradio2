#include "editlistradio.h"
#include "ui_editlistradio.h"

EditlistRadio::EditlistRadio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditlistRadio)
{
    ui->setupUi(this);

    background =    new QLabel(this);
    message    =    new QMessageBox(this);

    connect(ui->return_pushButton,  &QPushButton::clicked,  this,   &EditlistRadio::close_editor);          // закрываем окно
    connect(ui->reset_pushButton,   &QPushButton::clicked,  this, [this]() {emit reset_playlist();});       // сигнал сбросить плейлист
    connect(ui->Category_comboBox,  &QComboBox::currentIndexChanged, this, &EditlistRadio::changed_groups); // смена группы радио
    connect(ui->del_pushButton,     &QPushButton::clicked,  this,   &EditlistRadio::check_delete);          // удалить радиостанцию

}

EditlistRadio::~EditlistRadio()
{
    delete ui;
    delete background;
    delete message;
}

// ---------------------------- инициализация -------------------------------------

void EditlistRadio::init()
{
    background->resize(this->width(), this->height());
    background->lower();
    background->setStyleSheet("background-color: rgba(255, 255, 255, 0); border-image: url(:/res/vborder.png); ");
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);                       // делаем окно прозрачным
}

// --------------------------- закрыть окно редактора -----------------------------

void EditlistRadio::close_editor()
{
    this->close();
}

// -------------------------- получаем список названий радиостанции из базы данных ---------------------------

void EditlistRadio::get_name_radio(std::list <QString> r)
{
    nameRadio = r;
}

// -------------------------- получаем список групп радиостанции из базы данных ---------------------------

void EditlistRadio::get_group_radio(std::list <QString> r)
{
    groupsRadio = r;
}

// -------------------------- обновляем del_combobox -------------------------------------------------

void EditlistRadio::changed_groups()
{
    this->ui->del_comboBox->clear();
    this->ui->del_comboBox->addItem("");

    for(std::list<QString>::iterator it1=groupsRadio.begin(), it2=nameRadio.begin();
         (it1!=groupsRadio.end())&&(it2!=nameRadio.end());
         ++it1, ++it2)
    {
        if (*it1==ui->Category_comboBox->currentText())
        {
            this->ui->del_comboBox->addItem(*it2);
        }
    }
}

// --------------------------- проверка на возможность удаления радиостанции из базы --------------------------

void EditlistRadio::check_delete()
{
    if((ui->Category_comboBox->currentIndex()==0) or
       (ui->del_comboBox->currentIndex()==0))
    {
        message->setStyleSheet("background-color: lightblue; color: black; "
                               "font: 700 italic 14pt 'Times New Roman';");
        message->setText("<center><font color = 'red'>ВНИМАНИЕ !</center>");
        message->setInformativeText("<center> Не выбрана группа или радиостанция </center>");
        message->setIcon(QMessageBox::Critical);
        message->setStandardButtons(QMessageBox::Ok);
        message->setWindowFlag(Qt::FramelessWindowHint);
        message->show();
        return;
    } else
    {
        emit delete_yes();
    }
}

