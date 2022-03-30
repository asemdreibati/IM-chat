#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QVector>
#include<QJsonArray>
class ServerWorker;
/// @brief Represents the central server 
class ChatServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatServer)
public:
    explicit ChatServer(QObject *parent = nullptr);
protected:
    /// @brief Handles the incoming connect request .
    /// @param socketDescriptor 
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void logMessage(const QString &msg);
public slots:
    void stopServer();
private slots:
    /// @brief Send message to all users except the sender except in case it sends all online users.
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    /// @brief Send message to all users in a specific group.
    /// @param message 
    /// @param group_members .
    void multicast(const QJsonObject &message, QJsonArray group_members);
    /// @brief Send message to a specific user (private chat).
    /// @param message 
    /// @param destination 
    void unicast(const QJsonObject &message, ServerWorker *destination);
    /// @brief Receive a message from a client by his socket wrapper .
    /// @param sender 
    /// @param doc 
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender);
    void userError(ServerWorker *sender);
private:
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    /// @brief Send message to client by his socket wrapper.
    /// @param destination 
    /// @param message 
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    /// @brief Represents all users that connected to the server .
    QVector<ServerWorker *> m_clients;
};

#endif // CHATSERVER_H
