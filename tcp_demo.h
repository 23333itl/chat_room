#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>

#pragma pack(push, 1)
#include "protocol.h"
#pragma pack(pop)

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
   // void sendMessage(const QString &message);
    void sendMessage(const QString &message,int type);//发送消息体给服务器
    QTcpSocket* getsocket();
    void shutdown();
    void uploadFile(const QString &filePath);
    void sendFileMessage(const QByteArray &content, int type);
    void sendNextChunk();
    void requestDownloadFile(int fileId,QString filename);//请求下载文件
signals:
    void qq_connected();
    void qq_disconnected();
    void qq_recvmsg(QString& message);
    void uploadProgress(int percent);//上传文件进度
    void uploadComplete(bool success);//是否上传文件完成
    void qq_userlist(QStringList users);//用户列表
    void fileListReceived(QStringList files);
    void downloadProgress(int percent);        //下载进度
    void downloadComplete(bool success, QString filePath);  //下载完成
private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    QTcpSocket *socket;
    // // 消息结构体
    // struct ChatMsg {
    //     int totalLen;    // 1.总长 = sizeof(ChatMsg) + 内容长度
    //     int type;        // 2.类型 0=默认测试消息 1=登录 2=聊天 3=退出 4=心跳包 5=发送密码
    //     //char name[20];   // 3.发送者用户名
    //     char content[0]; // 3.标记内容地址
    // };
    //上传文件相关
    QFile *file=nullptr;
    int uploadFileId = 0;
    int uploadTotalChunks = 0;
    int currentChunk = 0;
    //下载文件相关
    QFile* downloadFile = nullptr;
    int downloadFileId = 0;
    int downloadTotalChunks = 0;
    int downloadCurrentChunk = 0;
    QString downloadFileName;

};

#endif
