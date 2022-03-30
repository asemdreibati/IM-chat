#ifndef CHATWITHGROUP_H
#define CHATWITHGROUP_H

#include <QDialog>
#include "chat.h"
#include "chatclient.h"
#include "chatwindow.h"

namespace Ui {
class ChatWithGroup;
}

/// @brief Manage the group dialog.
class ChatWithGroup : public Chat
{
    Q_OBJECT

public:
    /// @brief Constructor.
    explicit ChatWithGroup(QWidget *parent = 0,QVector<QString> group_members={} , ChatClient* member_socket=0);

    /// @brief Destructor.
    ~ChatWithGroup();

    /// @brief Send the input message to the corresponding socket wrapper.
    void send_message() override;

    /// @brief Set client socket .
    void set_group_members(QVector<QString> group_members)
    {
        for(int i=0;i<group_members.count();i++)
        {
            this->group_members_.append(group_members.at(i));
        }
    }

    /// @brief Returns group members .
    QVector<QString> get_group_members()
    {
        return this->group_members_;
    }


private slots:

    void recieve_message(QString sender, QString text,QVector<QString> group_members={});


private:
    /// @brief Represents the group window .
    Ui::ChatWithGroup *ui;

    /// @brief List of all group members .
    QVector<QString> group_members_;
};

#endif // CHATWITHGROUP_H
