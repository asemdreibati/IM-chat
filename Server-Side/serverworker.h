#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
class QJsonObject;
/// @brief Wrap a TCP socket to manage the server side actions  .
class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    /// @brief Get the name of the client. 
    /// @return 
    QString userName() const;
    /// @brief Set name to m_userName
    /// @param userName 
    void setUserName(const QString &userName);
    /// @brief Write the message on the actual socket .
    /// @param jsonData 
    void sendJson(const QJsonObject &jsonData);
signals:
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void logMessage(const QString &msg);
public slots:
    void disconnectFromClient();
private slots:
    void receiveJson();
private:
    /// @brief Represents the actual socket that is connecting with a specific socket in the client .
    QTcpSocket *m_serverSocket;
    /// @brief Holds the user name of the client .
    QString m_userName;
};

#endif // SERVERWORKER_H
