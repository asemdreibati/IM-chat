#include "chatwithgroup.h"
#include "ui_chatwithgroup.h"


ChatWithGroup::ChatWithGroup(QWidget *parent,QVector<QString> group_members, ChatClient *member_socket)
    :Chat::Chat(parent,member_socket),
    ui(new Ui::ChatWithGroup),
    group_members_(group_members)
{
    connect((ChatWindow *)parent , &ChatWindow::send_to_dialog, this, &ChatWithGroup::recieve_message);

    ui->setupUi(this);
    for(int i=0;i<group_members_.count();i++)
    {
        ui->group_members->addItem(group_members_.at(i));
    }

}

ChatWithGroup::~ChatWithGroup()
{
    delete ui;
}

void ChatWithGroup::send_message()
{
    if(! ui->input_field->text().isEmpty())
    {
        this->get_client_socket()->send_group_message(ui->input_field->text(),this->group_members_);
        ui->chat_panel->addItem("Me:");
        ui->chat_panel->addItem(ui->input_field->text());
        ui->input_field->setText("");
    }
}

void ChatWithGroup::recieve_message(QString sender, QString text, QVector<QString> group_members)
{
    if(sender != this->get_client_socket()->get_user_name())
    {
        ui->chat_panel->addItem(sender+":");
        ui->chat_panel->addItem(text);
    }

}


