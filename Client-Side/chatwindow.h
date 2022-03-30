#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
#include "chatwithone.h"
class ChatClient;
class QStandardItemModel;
namespace Ui { class ChatWindow; }

/// @brief Controls the interface in the client side. 
class ChatWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatWindow)
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private:
    /// @brief Holds the main window.
    Ui::ChatWindow *ui;
    /// @brief A socket wrapper to handle the communication with the server.
    ChatClient *m_chatClient;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;
    /// @brief Contains all users that the current user is chat with each one of them individually(Privately).
    QVector<QString> private_chats_;
    /// @brief Contains all users that the current user is chat with them in a group.
    QVector<QString> group_chats_;

private slots:
    /// @brief Show input dialog to insert the info which is nessecary to the connection to server.
    void attemptConnection();
    /// @brief after a successful connection,log the user .
    void connectedToServer();
    /// @brief Login the user.
    /// @param [in] userName 
    void attemptLogin(const QString &userName);
    /// @brief after login , enable some buttons to interact with it .
    void loggedIn();
    void loginFailed(const QString &reason);
    /// @brief Display the text which recieved and the sender in the chat section .
    /// @param sender 
    /// @param text 
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    /// @brief Display a new user connected in the app .
    /// @param username 
    void userJoined(const QString &username);
    /// @brief Display a new user disconnected in the app 
    /// @param username 
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
    /// @brief Display all online users in online users section .
    /// @param online_users 
    void show_online_users(const QJsonArray &online_users);
    /// @brief Trigger a dialog to do a private chat .
    void on_chat_with_selected_clicked();
    /// @brief Showing the received  private message in the private dialog.
    /// @param senderVal 
    /// @param textVal 
    void recive_private_message(QString senderVal,QString textVal);
    /// @brief Showing the received  message in the group dialog.
    /// @param senderVal 
    /// @param textVal 
    /// @param group_chats 
    void recive_group_message(QString senderVal,QString textVal,QVector<QString> group_chats);

    /// @brief Add a user to group list .
    void on_add_user_to_group_clicked();
    /// @brief Open group dialog after selecting users .
    void on_open_group_clicked();

signals:
    /// @brief Send information to the private dialog .
    void send_to_dialog(QString sender, QString text);
    /// @brief Send information to the group dialog .
    /// @param senderVal 
    /// @param textVal 
    /// @param group_chats 
    void send_to_group_dialog(QString senderVal,QString textVal,QVector<QString> group_chats);
};

#endif // CHATWINDOW_H
