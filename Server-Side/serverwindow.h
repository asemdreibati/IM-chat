#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>

namespace Ui {
class ServerWindow;
}

class ChatServer;
/// @brief Controls the interface in the Server side. 
class ServerWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWindow)
public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    /// @brief Holds the main window.
    Ui::ServerWindow *ui;
    /// @brief Represents the central server in each instance.
    ChatServer *m_chatServer;
private slots:
    void toggleStartServer();
    /// @brief Display the message in the server panel.
    /// @param msg 
    void logMessage(const QString &msg);
};

#endif // SERVERWINDOW_H
