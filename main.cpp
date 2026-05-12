#include "chat_login.h"
#include"tcp_demo.h"
#include"chat_room.h"
#include <QApplication>
#include<QTimer>
#include<QThread>
#include <QObject>
#include<QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     chat_login* login=new chat_login;
     chat_room* chat=new chat_room;
    TcpClient* client=new TcpClient;//连接对象
    QTimer* lo_timer=login->gettimer(); //用于连接超时
    QTimer* ping_timer=chat->gettimer(); //用与连接稳定
    QTcpSocket* tcp=client->getsocket();//套接字


    //信号与槽连接
    QObject::connect(login, &chat_login::qq_login, [&](){
        //qDebug()<<"qt_login start time";
        client->connectToServer("8.163.51.47", 9527);
        // 隐藏登录界面，显示主界面
        lo_timer->start(10000); //10s超时
    });
    login->show();

    QObject::connect(lo_timer, &QTimer::timeout, nullptr, [&]() {
        qDebug()<<"连接超时，请稍后尝试";
        login->set_stainfo("连接超时，请稍后尝试");
        //login->update();
        tcp->abort(); // 停止连接
        tcp->close();
    });

    // 连接成功 → 停止定时器
    QObject::connect(client, &TcpClient::qq_connected,  [&]() {
        lo_timer->stop();
        qDebug() << "已连接到服务器";
        login->set_stainfo("已连接到服务器");
        //QTread::sleep(2);
        QTimer::singleShot(2000,login,[&]{
            // client->sendMessage("hello Server!",1); // 连接成功后自动发送消息
            //client->sendMessage("hello Server!",0); // 连接成功后自动发送消息
            client->sendMessage(login->getname(),1);
            client->sendMessage(login->getpassword(),5);
            chat->setusername(login->getname());
            login->hide();
            chat->show();
            ping_timer->start(5000);//每隔5s检测连接性
            //qDebug()<<"ping_timer started";
        });//延迟2s后进入聊天室

    });

    //检测连接性
    QObject::connect(ping_timer,&QTimer::timeout,chat,[&](){
        ping_timer->stop();
        //qDebug()<<"发送心跳包";
        client->sendMessage("",4);
        ping_timer->start(5000);
    });

    // 连接失败 → 停止定时器
    QObject::connect(tcp, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), client, [&]() {
        if(login->isVisible()){
        qDebug()<<"服务器连接失败，请稍后尝试";
        login->set_stainfo("服务器连接失败，请稍后尝试");
        //login->update();
        lo_timer->stop();
        }
    });

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&](){
        client->shutdown();
    });

    QObject::connect(client,&TcpClient::qq_disconnected,[&](){
        if(chat->isVisible()){
        ping_timer->stop();
        chat->hide();
        login->show();
        QMessageBox::information(login,"网络出错","连接已断开");
        }
    });

    QObject::connect(client,&TcpClient::qq_recvmsg,chat,[&](QString& message){
        chat->addMessage(message,false);
    });

    QObject::connect(chat,&chat_room::sendmessage,tcp,[&](const QString msg){
        client->sendMessage(msg,2);
    });
    //文件功能
    QObject::connect(chat,&chat_room::uploadfile,tcp,[&](const QString filePath){
        client->uploadFile(filePath);
    });

    QObject::connect(client, &TcpClient::uploadProgress, chat, [=](int percent){
        chat->setfilepro(percent);
    });

    QObject::connect(client, &TcpClient::uploadComplete, chat, [=](bool success){
        chat->setfilesta(success);
    });
    //更新在线成员
    QObject::connect(client, &TcpClient::qq_userlist, chat, &chat_room::updateUserList);

    //更新文件列表
    QObject::connect(client,&TcpClient::fileListReceived,chat,&chat_room::updateFileList);

    //获取(下载)文件
    QObject::connect(chat,&chat_room::requestDownload,client,[&](int id,QString name){
        client->requestDownloadFile(id,name);
    });

    // 下载进度和完成
    QObject::connect(client, &TcpClient::downloadProgress, chat, &chat_room::onDownloadProgress);
    QObject::connect(client, &TcpClient::downloadComplete, chat, &chat_room::onDownloadComplete);
    // QObject::connect(tcp, &QTcpSocket::readyRead, [&](){
    //     qDebug() << "READY READ! bytes:" << tcp->bytesAvailable();
    //     QByteArray data = tcp->readAll();
    //     qDebug() << "RAW DATA:" << data.toHex();
    // });


    //qDebug()<<"进入事件循环";

    // chat->show();



    return a.exec();


    // QCoreApplication a(argc, argv);



    // //qDebug() << "输入消息 (输入 'quit' 退出):";
    // int count=0;
    // QTimer inputTimer;
    // QObject::connect(&inputTimer, &QTimer::timeout, [&]() {
    //     for(int i=0;i<5;i++){
    //         client.sendMessage("hello"+QString::number(i));
    //         count++;
    //     }
    //     if(count==5){
    //     inputTimer.stop();
    //     a.quit();
    //     }
    // });
    // inputTimer.start(5000);  // 每5s检查一次

    // return a.exec();
}
