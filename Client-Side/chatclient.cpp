#include "chatclient.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), this, &ChatClient::error);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

QString ChatClient::get_user_name() const
{
    if(! user_name_.isEmpty())
        return user_name_;
    return "";

}

void ChatClient::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected
        user_name_=userName;
        QDataStream clientStream(m_clientSocket);
        clientStream.setVersion(QDataStream::Qt_5_7);
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("login");
        message[QStringLiteral("username")] = userName;
        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}

void ChatClient::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return;
    QDataStream clientStream(m_clientSocket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("text")] = text;
    clientStream << QJsonDocument(message).toJson();
}

void ChatClient::send_private_message(const QString &text,const QString &destination )
{
    if (text.isEmpty())
        return;
    QDataStream clientStream(m_clientSocket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("private");
    message[QStringLiteral("text")] = text;
    message[QStringLiteral("reciever")] = destination;
    clientStream << QJsonDocument(message).toJson();
}

void ChatClient::send_group_message(const QString &text, const QVector<QString> &group_members)
{
    if (text.isEmpty())
        return;
    QDataStream clientStream(m_clientSocket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("group");
    message[QStringLiteral("text")] = text;
    QJsonArray group_members_json;
    for(int i=0;i<group_members.count();i++)
    {
        group_members_json.append(group_members.at(i));
    }
    message[QStringLiteral("group_members")] =group_members_json;
    clientStream << QJsonDocument(message).toJson();
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

void ChatClient::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message
        if (m_loggedIn)
            return;
        const QJsonValue resultVal = docObj.value(QLatin1String("success"));
        if (resultVal.isNull() || !resultVal.isBool())
            return; // the message had no success field so we ignore
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {
            emit loggedIn();
            return;
        }
        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) { //It's a chat message
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return;
        if (senderVal.isNull() || !senderVal.isString())
            return;
        emit messageReceived(senderVal.toString(), textVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) { // A user joined the chat
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return;
        emit userJoined(usernameVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) { // A user left the chat
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return;
        emit userLeft(usernameVal.toString());
    }else if (typeVal.toString().compare(QLatin1String("online"), Qt::CaseInsensitive) == 0) { // All Online users
          const QJsonValue online_users = docObj.value(QLatin1String("users"));
          if (online_users.isNull() || !online_users.isArray())
              return;
          emit show_online_users(online_users.toArray());
     }else if (typeVal.toString().compare(QLatin1String("private"), Qt::CaseInsensitive) == 0) { // Private message
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        if (textVal.isNull() || !textVal.isString())
            return;
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (senderVal.isNull() || !senderVal.isString())
            return;

        const QJsonValue recieverVal = docObj.value(QLatin1String("reciever"));
        if (recieverVal.isNull() || !recieverVal.isString())
            return;

        emit recive_private_message(senderVal.toString(),textVal.toString());
   }else if (typeVal.toString().compare(QLatin1String("group"), Qt::CaseInsensitive) == 0) { // Group message
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        if (textVal.isNull() || !textVal.isString())
            return;
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (senderVal.isNull() || !senderVal.isString())
            return;

        const QJsonValue group_members = docObj.value(QLatin1String("group_members"));
        if (group_members.isNull() || !group_members.isArray())
            return;
        QVector<QString> group_members_vec;
        for(int i=0;i<docObj.value(QLatin1String("group_members")).toArray().size();i++)
        {
            group_members_vec.append(docObj.value(QLatin1String("group_members")).toArray().at(i).toString());
        }
        emit recive_group_message(senderVal.toString(),textVal.toString(),group_members_vec);
   }
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

void ChatClient::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_7);
    for (;;) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    jsonReceived(jsonDoc.object());
            }
        } else {
            break;
        }
    }
}
