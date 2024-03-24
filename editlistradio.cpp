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
    connect(ui->add_pushButton,     &QPushButton::clicked,  this,   &EditlistRadio::check_add);             // добавить радиостанцию

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
    changed_groups();
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
        message->setStyleSheet("background-color: lightblue; color: black; "
                               "font: 700 italic 14pt 'Times New Roman';");
        message->setText("<center><font color = 'red'>ВНИМАНИЕ !</center>");
        message->setInformativeText("<center> Вы действительно хотите удалить "
                                    "радиостанцию <font color='blue'>"
                                    "'"+ui->del_comboBox->currentText()+"'"
                                    "<font color='black'>? </center>");
        message->setIcon(QMessageBox::Warning);
        message->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        message->setWindowFlag(Qt::FramelessWindowHint);

        message->show();

        int ret = message->exec();

        switch (ret)
        {
        case QMessageBox::Cancel:
        {
            return;
        } break;
        case QMessageBox::Ok:
        {
            message->setStyleSheet("background-color: lightblue; color: black; "
                                   "font: 700 italic 14pt 'Times New Roman';");
            message->setText("<center><font color = 'red'>Радиостанция "+ui->del_comboBox->currentText()+"</center>");
            message->setInformativeText("<center> удалена из плейлиста </center>");
            message->setIcon(QMessageBox::Information);
            message->setStandardButtons(QMessageBox::Ok);
            message->setWindowFlag(Qt::FramelessWindowHint);
            message->show();

            emit delete_yes(ui->del_comboBox->currentText());
        } break;
        }
    }
}

// --------------------------- проверка можно ли добавить радиостанцию в плейлист --------------------------------

void EditlistRadio::check_add()
{
    QString str_name = ui->add_name_lineEdit->text();
    QString str_url  = ui->add_url_lineEdit->text();
    QString str_group = ui->Category_comboBox->currentText();

    // Сначала проверяем все ли необходимые поля заполнены

    if(ui->Category_comboBox->currentIndex()==0)
    {
        message->setStyleSheet("background-color: lightblue; color: black; "
                               "font: 700 italic 14pt 'Times New Roman';");
        message->setText("<center><font color = 'red'>ВНИМАНИЕ !!!</center>");
        message->setInformativeText("<center> не выбранна группа радиостанций </center>");
        message->setIcon(QMessageBox::Warning);
        message->setStandardButtons(QMessageBox::Ok);
        message->setWindowFlag(Qt::FramelessWindowHint);
        message->show();
        return;
    }
    if((str_name.isEmpty()) or str_name.count(' ')==str_name.size())
    {
        message->setStyleSheet("background-color: lightblue; color: black; "
                               "font: 700 italic 14pt 'Times New Roman';");
        message->setText("<center><font color = 'red'>ВНИМАНИЕ !!!</center>");
        message->setInformativeText("<center> не введено название радиостанции </center>");
        message->setIcon(QMessageBox::Warning);
        message->setStandardButtons(QMessageBox::Ok);
        message->setWindowFlag(Qt::FramelessWindowHint);
        message->show();
        return;
    }
    if((str_url.isEmpty()) or (str_url.count(' ')==str_url.size()))
    {
        message->setStyleSheet("background-color: lightblue; color: black; "
                               "font: 700 italic 14pt 'Times New Roman';");
        message->setText("<center><font color = 'red'>ВНИМАНИЕ !!!</center>");
        message->setInformativeText("<center> не введено url радиостанции </center>");
        message->setIcon(QMessageBox::Warning);
        message->setStandardButtons(QMessageBox::Ok);
        message->setWindowFlag(Qt::FramelessWindowHint);
        message->show();
        return;
    }

    emit add_radio(str_group, str_name, str_url);    // передаем сигнал для добавления радио в базу данных

    message->setStyleSheet("background-color: lightblue; color: black; "
                           "font: 700 italic 14pt 'Times New Roman';");
    message->setText("<center><font color = 'red'>ВНИМАНИЕ !!!</center>");
    message->setInformativeText("<center> Радиостанция "+str_name+" добавлена в группу "+str_group+" !!! </center>");
    message->setIcon(QMessageBox::Information);
    message->setStandardButtons(QMessageBox::Ok);
    message->setWindowFlag(Qt::FramelessWindowHint);
    message->show();

    ui->add_name_lineEdit->clear();
    ui->add_url_lineEdit->clear();
}
