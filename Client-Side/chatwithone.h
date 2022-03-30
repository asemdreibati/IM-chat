#ifndef CHATWITHONE_H
#define CHATWITHONE_H

#include <QDialog>
#include "chatclient.h"
#include "chatwindow.h"

namespace Ui {
class ChatWithOne;
}
/// @brief Manage the private dialog.
class ChatWithOne : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWithOne(QWidget *parent = 0 ,QString user_destination="" , ChatClient* socket_wrapper=0 );
    ~ChatWithOne();
    /// @brief Send the input message to the corresponding socket wrapper.
    void sendMessage();

    QString get_user_destination();
private slots:
    /// @brief Receive a message from the main window to display it in the dialog.
    void recieve_message(QString sender, QString text);
    /// @brief trigger send message metod.
    void on_send_button_clicked();
    /// @brief Cancel the dialog .
    void on_cancel_clicked();

private:
    Ui::ChatWithOne *ui;
    QString user_destination_;
    /// @brief Wrapper socket which is the same as in the parent (Main window ) to handle the communications as the same user.
    ChatClient *socket_wrapper_;

};

#endif // CHATWITHONE_H
