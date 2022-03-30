#ifndef CHAT_H
#define CHAT_H
#include <QDialog>
#include"ChatClient.h"

/// @brief Abstract class for chat modes .
class Chat : public QDialog
{
    Q_OBJECT

public:
    /// @brief Constructor .
    explicit Chat(QWidget *parent=0,ChatClient* client_socket=0):QDialog(parent){
        this->client_socket_=client_socket;
    }

    /// @brief Send the input message to the corresponding socket wrapper.
    virtual void send_message()=0;

    /// @brief Set client socket .
    void set_client_socket(ChatClient* client_socket)
    {
        this->client_socket_=client_socket;
    }

    /// @brief get client socket .
    ChatClient* get_client_socket()
    {
        return this->client_socket_;
    }

protected slots:
    /// @brief Receive the message from the corresponding socket to display it  .
    /// @param sender
    /// @param text
    /// @param group_members
    virtual void recieve_message(QString sender, QString text,QVector<QString> group_members={})=0;

    /// @brief Cancel the dialog .
    void on_cancel_button_clicked(){
        this->close();
    }

    /// @brief Send the message by socket .
    void on_send_button_clicked()
    {
        this->send_message();
    }

private:
   /// @brief Wrapper socket which is the same as in the parent (Main window ) to handle the communications as the same user.
   ChatClient* client_socket_;
};


#endif // CHAT_H
