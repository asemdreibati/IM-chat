#ifndef CHATWITHGROUP_H
#define CHATWITHGROUP_H

#include <QDialog>
#include "chatclient.h"
#include "chatwindow.h"
namespace Ui {
class ChatWithGroup;
}

class ChatWithGroup : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWithGroup(QWidget *parent = 0,QVector<QString> group_members={} , ChatClient* member_socket=0);
    ~ChatWithGroup();
    void sendMessage();


private slots:
    void on_pushButton_clicked();
    void recieve_message(QString sender, QString text,QVector<QString> group_members);


private:
    Ui::ChatWithGroup *ui;
    QVector<QString> group_members_;
   ChatClient* member_socket_;
};

#endif // CHATWITHGROUP_H
