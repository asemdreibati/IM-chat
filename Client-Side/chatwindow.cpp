#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "chatclient.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include<QDebug>
#include<QMessageBox>

#include"ChatWithOne.h"
#include"chatwithgroup.h"
ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
    , m_chatClient(new ChatClient(this))
    , m_chatModel(new QStandardItemModel(this))

{
    ui->setupUi(this);
    m_chatModel->insertColumn(0);
    ui->chatView->setModel(m_chatModel);
    connect(m_chatClient, &ChatClient::connected, this, &ChatWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::loggedIn, this, &ChatWindow::loggedIn);
    connect(m_chatClient, &ChatClient::loginError, this, &ChatWindow::loginFailed);
    connect(m_chatClient, &ChatClient::messageReceived, this, &ChatWindow::messageReceived);
    connect(m_chatClient, &ChatClient::disconnected, this, &ChatWindow::disconnectedFromServer);
    connect(m_chatClient, &ChatClient::error, this, &ChatWindow::error);
    connect(m_chatClient, &ChatClient::userJoined, this, &ChatWindow::userJoined);
    connect(m_chatClient, &ChatClient::userLeft, this, &ChatWindow::userLeft);
    connect(ui->connectButton, &QPushButton::clicked, this, &ChatWindow::attemptConnection);
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->messageEdit, &QLineEdit::returnPressed, this, &ChatWindow::sendMessage);
    connect(m_chatClient, &ChatClient::show_online_users, this, &ChatWindow::show_online_users);
    connect(m_chatClient, &ChatClient::recive_private_message, this, &ChatWindow::recive_private_message, Qt::QueuedConnection);
    connect(m_chatClient, &ChatClient::recive_group_message, this, &ChatWindow::recive_group_message, Qt::QueuedConnection);

}


ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::attemptConnection()
{
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Chose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );
    if (hostAddress.isEmpty())
        return;
    ui->connectButton->setEnabled(false);
    m_chatClient->connectToServer(QHostAddress(hostAddress), 1967);
}

void ChatWindow::connectedToServer()
{
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        return m_chatClient->disconnectFromHost();
    }
    attemptLogin(newUsername);
}

void ChatWindow::attemptLogin(const QString &userName)
{
    m_chatClient->login(userName);
}

void ChatWindow::loggedIn()
{
    ui->sendButton->setEnabled(true);
    ui->messageEdit->setEnabled(true);
    ui->chatView->setEnabled(true);
    m_lastUserName.clear();
}

void ChatWindow::loginFailed(const QString &reason)
{
    QMessageBox::critical(this, tr("Error"), reason);
    connectedToServer();
}

void ChatWindow::messageReceived(const QString &sender, const QString &text)
{
    int newRow = m_chatModel->rowCount();
    if (m_lastUserName != sender) {
        m_lastUserName = sender;
        QFont boldFont;
        boldFont.setBold(true);
        m_chatModel->insertRows(newRow, 2);
        m_chatModel->setData(m_chatModel->index(newRow, 0), sender + QLatin1Char(':'));
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        m_chatModel->setData(m_chatModel->index(newRow, 0), boldFont, Qt::FontRole);
        ++newRow;
    } else {
        m_chatModel->insertRow(newRow);
    }
    m_chatModel->setData(m_chatModel->index(newRow, 0), text);
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    ui->chatView->scrollToBottom();
}

void ChatWindow::sendMessage()
{
    m_chatClient->sendMessage(ui->messageEdit->text());
    const int newRow = m_chatModel->rowCount();
    m_chatModel->insertRow(newRow);
    m_chatModel->setData(m_chatModel->index(newRow, 0), ui->messageEdit->text());
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    ui->messageEdit->clear();
    ui->chatView->scrollToBottom();
    m_lastUserName.clear();
}

void ChatWindow::disconnectedFromServer()
{
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);
    ui->chatView->setEnabled(false);
    ui->connectButton->setEnabled(true);
    m_lastUserName.clear();
}

void ChatWindow::userJoined(const QString &username)
{
    const int newRow = m_chatModel->rowCount();
    m_chatModel->insertRow(newRow);
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Joined the Chat").arg(username));
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::blue), Qt::ForegroundRole);
    ui->chatView->scrollToBottom();
    m_lastUserName.clear();
}
void ChatWindow::userLeft(const QString &username)
{
    const int newRow = m_chatModel->rowCount();
    m_chatModel->insertRow(newRow);
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Left the Chat").arg(username));
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::red), Qt::ForegroundRole);
    ui->chatView->scrollToBottom();
    m_lastUserName.clear();
}

void ChatWindow::error(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
    ui->connectButton->setEnabled(true);
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);
    ui->chatView->setEnabled(false);
    m_lastUserName.clear();
}



void ChatWindow::show_online_users(const QJsonArray &online_users)
{
    ui->listWidget->clear();
    for(int i=0;i<online_users.size();i++)
    {
        if(online_users.at(i)==m_chatClient->get_user_name())
            continue;
        ui->listWidget->addItem(QString(online_users.at(i).toString()));
    }
}


void ChatWindow::on_chat_with_selected_clicked()
{
    if( ui->listWidget->count()>0 && ui->listWidget->selectedItems().count()>0){
        QString user_name=ui->listWidget->currentItem()->text();
        if(! this->private_chats_.contains(user_name))
        {
            this->private_chats_.append(user_name);
            ChatWithOne dialog(this,user_name,this->m_chatClient);
            dialog.setModal(true);
            dialog.exec();
            this->private_chats_.removeOne(user_name);
        }
    }


}

void ChatWindow::recive_private_message(QString sender, QString text)
{

    if(!this->private_chats_.contains(sender) ){
        this->private_chats_.append(sender);
        ChatWithOne dialog(this,sender,this->m_chatClient);
        dialog.setModal(true);
        emit send_to_dialog(sender,text);
        dialog.exec();
        this->private_chats_.removeOne(sender);
        return;
    }
     emit send_to_dialog(sender,text);


}

void ChatWindow::recive_group_message(QString senderVal, QString textVal,QVector<QString> group_chats)
{
    if(group_chats_.isEmpty())
    {
        for(int i=0;i<group_chats.size();i++)
        group_chats_.append(group_chats.at(i));
        ChatWithGroup dialog(this,group_chats_,this->m_chatClient);
        dialog.setModal(true);
        emit send_to_group_dialog(senderVal,textVal,group_chats_);
        dialog.exec();
        this->group_chats_.clear();
        return;
    }
     emit send_to_group_dialog(senderVal,textVal,group_chats_);
}



void ChatWindow::on_add_user_to_group_clicked()
{
    if( ui->listWidget->count()>0 && ui->listWidget->selectedItems().count()>0){
        QString user_name=ui->listWidget->currentItem()->text();
        if(! this->group_chats_.contains(user_name))
        {
            this->group_chats_.append(user_name);
        }
    }
}

void ChatWindow::on_open_group_clicked()
{
    if(this->group_chats_.count()>0)
    {
        if(this->group_chats_.count()==1)
        {
            QMessageBox::warning(this,"Warning","You've added just one user , you can chat him/her privately instead .");
            return;
        }
        group_chats_.append(this->m_chatClient->get_user_name());
        ChatWithGroup dialog(this,group_chats_,this->m_chatClient);
        dialog.setModal(true);
        dialog.exec();
        this->group_chats_.clear();


    }
}
