#include "chatwithone.h"
#include "ui_chatwithone.h"

ChatWithOne::ChatWithOne(QWidget *parent, QString user_name , ChatClient* user_socket) :
    Chat::Chat(parent,user_socket),
    ui(new Ui::ChatWithOne),
    user_name_(user_name)
{
    connect((ChatWindow *)parent , &ChatWindow::send_to_dialog, this, &ChatWithOne::recieve_message);
    ui->setupUi(this);
}

ChatWithOne::~ChatWithOne()
{
    delete ui;
}

QString ChatWithOne::get_user_name()
{
    return user_name_;
}

void ChatWithOne::send_message()
{

    if(!ui->input_field->text().isEmpty())
    {
        this->get_client_socket()->send_private_message(ui->input_field->text(),this->user_name_);
        ui->chat_panel->addItem("Me:");
        ui->chat_panel->addItem(ui->input_field->text());
        ui->input_field->setText("");
    }
}

void ChatWithOne::recieve_message(QString sender, QString text,QVector<QString> group_members)
{
    ui->chat_panel->addItem(sender+":");
    ui->chat_panel->addItem(text);
}
