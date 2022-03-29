#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
#include "chatwithone.h"
class ChatClient;
class QStandardItemModel;
namespace Ui { class ChatWindow; }
class ChatWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatWindow)
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private:
    Ui::ChatWindow *ui;
    ChatClient *m_chatClient;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;
    QVector<QString> private_chats_;

private slots:
    void attemptConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
    void show_online_users(const QJsonArray &online_users);
    void on_chat_with_selected_clicked();
    void recive_private_message(QString senderVal,QString textVal);

signals:
    void send_to_dialog(QString sender, QString text);
};

#endif // CHATWINDOW_H
