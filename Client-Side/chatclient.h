#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>
#include<QVector>

class QHostAddress;
class QJsonDocument;
/// @brief Wrap a TCP socket to interact with the sever .
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
    /// @brief Get the user name .
    /// @return 
    QString get_user_name() const;
    /// @brief Write a private message on the socket in JSON format so that the corresponding socket on server will have the  information .
    /// @param text 
    /// @param destination 
    void send_private_message(const QString &text,const QString &destination );
    /// @brief Write a group message on the socket in JSON format  so that the corresponding socket on server will have the  information .
    /// @param text 
    /// @param group_members 
    void send_group_message(const QString &text,const QVector<QString> &group_members );

public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    /// @brief Write on the actual socket so that the corresponding socket on server will have the same information .
    /// @param text 
    void sendMessage(const QString &text);
    /// @brief Disconnect the socket.
    void disconnectFromHost();
private slots:
    /// @brief When the actual socket receive a message from the corresponding socket on the server ,this method is invoked.
    void onReadyRead();
signals:
    /// @brief when a socket is connected this signals is triggered to tell the main window  .
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    /// @brief Notify the main window to add a new message in the chat. 
    /// @param sender 
    /// @param text 
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    /// @brief Notify the main window that a client has been joined the app . 
    /// @param username 
    void userJoined(const QString &username);
    /// @brief Notify the main window that a client has been left the app. 
    /// @param username 
    void userLeft(const QString &username);
    /// @brief Send a command to main window to receive online users. 
    /// @param online_users 
    void show_online_users(const QJsonArray &online_users);
    /// @brief Send a command to main window to receive a group message. 
    /// @param senderVal 
    /// @param textVal 
    void recive_private_message(QString senderVal,QString textVal);
    /// @brief Send a command to main window to receive a group message. 
    /// @param senderVal 
    /// @param textVal 
    /// @param group_chats 
    void recive_group_message(QString senderVal,QString textVal,QVector<QString> group_chats);
private:
    /// @brief The actual socket that handle the communication with the srver .
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    /// @brief Handles the message which is sended by the server  .
    /// @param doc 
    void jsonReceived(const QJsonObject &doc);
    /// @brief this enable us to know which user related to a specific socket.
    QString user_name_;

};

#endif // CHATCLIENT_H
