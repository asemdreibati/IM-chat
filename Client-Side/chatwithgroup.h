#ifndef CHATWITHGROUP_H
#define CHATWITHGROUP_H

#include <QDialog>
#include "chatclient.h"
#include "chatwindow.h"
namespace Ui {
class ChatWithGroup;
}
/// @brief Manage the group dialog.
class ChatWithGroup : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWithGroup(QWidget *parent = 0,QVector<QString> group_members={} , ChatClient* member_socket=0);
    ~ChatWithGroup();
    /// @brief Send the input message to the corresponding socket wrapper.
    void sendMessage();


private slots:

    void on_pushButton_clicked();
    /// @brief Receive the message from the corresponding socket to display it  .
    /// @param sender 
    /// @param text 
    /// @param group_members 
    void recieve_message(QString sender, QString text,QVector<QString> group_members);
    /// @brief Cancel the dialog .
    void on_cancel_clicked();

private:
    Ui::ChatWithGroup *ui;
    /// @brief List of all group members .
    QVector<QString> group_members_;
   /// @brief Wrapper socket which is the same as in the parent (Main window ) to handle the communications as the same user.
   ChatClient* member_socket_;
};

#endif // CHATWITHGROUP_H
