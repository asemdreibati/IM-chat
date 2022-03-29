#include "chatwithone.h"
#include "ui_chatwithone.h"
#include "chatwindow.h"

ChatWithOne::ChatWithOne(QWidget *parent, QString user_destination , ChatClient* socket_wrapper) :
    QDialog(parent),
    ui(new Ui::ChatWithOne),
    user_destination_(user_destination),
    socket_wrapper_(socket_wrapper)
{
    connect((ChatWindow *)parent , &ChatWindow::send_to_dialog, this, &ChatWithOne::recieve_message);

    ui->setupUi(this);
}

ChatWithOne::~ChatWithOne()
{
    delete ui;
}

QString ChatWithOne::get_user_destination()
{
    return user_destination_;
}

void ChatWithOne::sendMessage()
{

    socket_wrapper_->send_private_message(ui->lineEdit->text(),this->user_destination_);
    //socket_wrapper_->sendMessage(ui->lineEdit->text());
    ui->listWidget->addItem("Me:");
    ui->listWidget->addItem(ui->lineEdit->text());
    ui->lineEdit->setText("");
}

void ChatWithOne::recieve_message(QString sender, QString text)
{
    ui->listWidget->addItem(sender+":");
    ui->listWidget->addItem(text);
}

void ChatWithOne::on_pushButton_clicked()
{
    sendMessage();
}
