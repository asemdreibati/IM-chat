#include "chatwithgroup.h"
#include "ui_chatwithgroup.h"

ChatWithGroup::ChatWithGroup(QWidget *parent,QVector<QString> group_members, ChatClient *member_socket) :
    QDialog(parent),
    ui(new Ui::ChatWithGroup),
    group_members_(group_members),
    member_socket_(member_socket)
{
    connect((ChatWindow *)parent , &ChatWindow::send_to_group_dialog, this, &ChatWithGroup::recieve_message);

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

void ChatWithGroup::sendMessage()
{
    if(! ui->lineEdit->text().isEmpty())
    {
        member_socket_->send_group_message(ui->lineEdit->text(),this->group_members_);
        ui->listWidget->addItem("Me:");
        ui->listWidget->addItem(ui->lineEdit->text());
        ui->lineEdit->setText("");
    }
}

void ChatWithGroup::on_pushButton_clicked()
{
    this->sendMessage();

}

void ChatWithGroup::recieve_message(QString sender, QString text, QVector<QString> group_members)
{
    if(sender != this->member_socket_->get_user_name())
    {
        ui->listWidget->addItem(sender+":");
        ui->listWidget->addItem(text);
    }

}

