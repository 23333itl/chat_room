#ifndef CHAT_LOGIN_H
#define CHAT_LOGIN_H

#include <QWidget>
#include<QMouseevent>
#include<QMenu>
#include<QAction>
#include<QStatusBar>
//#include"chat_room.h"
#include"tcp_demo.h"
#pragma pack(push, 1)
#include "protocol.h"
#pragma pack(pop)
#include<QTimer>
namespace Ui {
class chat_login;
}

class chat_login : public QWidget
{
    Q_OBJECT
private slots:
     void slot_exitApp();

    void on_btn_login_clicked();

signals:
     void qq_login();

public:
    explicit chat_login(QWidget *parent = nullptr);
    QTimer* gettimer();
    void set_stainfo(QString message);
    QString getname();
    QString getpassword();
    ~chat_login();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    Ui::chat_login *ui;
    QPoint m_pos;
    QMenu* exitmenu;//右键退出
    QAction* exitact;
    TcpClient *client_login;
    QTimer* connect_timer; //连接不上超时管理
    QStatusBar* sta;
    QString name;
    QString password;

};

#endif // CHAT_LOGIN_H
