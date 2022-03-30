#ifndef CHATWITHONE_H
#define CHATWITHONE_H

#include <QDialog>
#include "chatclient.h"
#include "chatwindow.h"
#include "chat.h"

namespace Ui {
class ChatWithOne;
}

/// @brief Manage the private dialog.
class ChatWithOne : public Chat
{
    Q_OBJECT

public:

    /// @brief Constructor.
    explicit ChatWithOne(QWidget *parent = 0 ,QString user_name="" , ChatClient* user_socket=0 );

    /// @brief Destructor.
    ~ChatWithOne();

    /// @brief Send the input message to the corresponding socket wrapper.
    void send_message() override;

    QString get_user_name();

private slots:

    /// @brief Receive a message from the main window to display it in the dialog.
    void recieve_message(QString sender, QString text,QVector<QString> group_members={});


private:

    /// @brief Represents the private chat window .
    Ui::ChatWithOne *ui;

    /// @brief Clinent name.
    QString user_name_;
};

#endif // CHATWITHONE_H
