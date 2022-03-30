#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>
#include<QVector>

class QHostAddress;
class QJsonDocument;
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
    QString get_user_name() const;
    void send_private_message(const QString &text,const QString &destination );
    void send_group_message(const QString &text,const QVector<QString> &group_members );

public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    void sendMessage(const QString &text);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void show_online_users(const QJsonArray &online_users);

    void recive_private_message(QString senderVal,QString textVal);
    void recive_group_message(QString senderVal,QString textVal,QVector<QString> group_chats);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
    QString user_name_;

};

#endif // CHATCLIENT_H
