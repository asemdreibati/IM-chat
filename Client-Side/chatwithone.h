#ifndef CHATWITHONE_H
#define CHATWITHONE_H

#include <QDialog>
#include "chatclient.h"
#include "chatwindow.h"

namespace Ui {
class ChatWithOne;
}

class ChatWithOne : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWithOne(QWidget *parent = 0 ,QString user_destination="" , ChatClient* socket_wrapper=0 );
    ~ChatWithOne();
    void sendMessage();

    QString get_user_destination();
private slots:
    void recieve_message(QString sender, QString text);

    void on_pushButton_clicked();

private:
    Ui::ChatWithOne *ui;
    QString user_destination_;
    ChatClient *socket_wrapper_;

};

#endif // CHATWITHONE_H
