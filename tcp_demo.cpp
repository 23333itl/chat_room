#include "tcp_demo.h"
#include"chat_room.h"
#include <QNetworkInterface>
#include <QHostAddress>
#include <string.h>
#include <QFileInfo>
#include <QRandomGenerator>
#include<QCoreApplication>
#include<QDir>
TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);



    // 连接信号槽
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &TcpClient::onErrorOccurred);
    //文件
    // // 文件上传信号
    // connect(client, &TcpClient::uploadProgress, this, [=](int percent){
    //     ui->progressBar->setValue(percent);
    // });

    // connect(client, &TcpClient::uploadComplete, this, [=](bool success){
    //     if (success) {
    //         ui->lblStatus->setText("上传成功");
    //         QMessageBox::information(this, "完成", "文件上传成功");
    //     } else {
    //         ui->lblStatus->setText("上传失败");
    //         QMessageBox::warning(this, "错误", "文件上传失败");
    //     }
    //     ui->btnSelectFile->setEnabled(true);
    // });
}

void TcpClient::connectToServer(const QString &host, quint16 port)
{
    qDebug() << "正在连接到" << host << ":" << port;
    socket->connectToHost(host, port);
    // if(socket->isOpen())
    // {
    //     // 客户端本地IP
    //     QHostAddress localAddr =socket->localAddress();
    //     // 客户端本地随机端口
    //     // localPort = socket->localPort();

    //     qDebug() << "客户端通信IP：" << localAddr.toString();
    //     // qDebug() << "客户端本地端口：" << localPort;
    // }
}

// void TcpClient::sendMessage(const QString &message)
// {

//     if(socket->state() == QAbstractSocket::ConnectedState) {
//         socket->write(message.toUtf8()+"\n");
//         socket->flush();
//         qDebug() << "发送:" << message;
//     } else {
//         qDebug() << "未连接到服务器";
//     }
// }

void TcpClient::sendMessage(const QString &message, int type)
{
    //将收到的类型和消息转成自己定义的message类型
    QByteArray content_utf8=message.toUtf8();//QString 转UTF-8编码
    int len=content_utf8.size();
    int Total_len=sizeof(ChatMsg)+len;
    ChatMsg* msg=(ChatMsg*)malloc(Total_len);
    msg->totalLen=Total_len;
    msg->type=type;
    memcpy(msg->content,content_utf8.constData(),len);
    //发送数据
    if(socket->state() == QAbstractSocket::ConnectedState) {
        // if(type==0){
        //     socket->write((const char*)msg,Total_len);
        //    // socket->flush();
        //     //qDebug() << "发送:" << message<<" 总长度:"<<msg->totalLen;
        //     qDebug() << "发送:" << message;
        // }
        // if(type==1){
        //     socket->write((const char*)msg,Total_len);
        //     // socket->flush();
        //     //qDebug() << "发送:" << message<<" 总长度:"<<msg->totalLen;
        //     qDebug() << "发送:" << message;
        // }
        // if(type==2){
        //    // qDebug()<<"已发送type=2";
        //     socket->write((const char*)msg,Total_len);
        // }
        // if(type==4){
        //     socket->write((const char*)msg,Total_len);
        // }
        // if(type==5){
        //     socket->write((const char*)msg,Total_len);
        // }
        // //type==6时专门走sendFileMessage函数
        // // if(type==6){

        // // }
        // if(type==8){
        //     socket->write((const char*)msg,Total_len);
        // }
        socket->write((const char*)msg,Total_len);
        // else{
        // socket->write(message.toUtf8()+"\n");
        // socket->flush();
        // qDebug() << "发送:" << message;
        // }
    }
    else {
        qDebug() << "未连接到服务器";
    }
    free(msg);
}



QTcpSocket *TcpClient::getsocket()
{
    return socket;
}

void TcpClient::shutdown()
{
    {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            //this->sendMessage("Quit",0);
                //socket->flush();
            socket->disconnectFromHost();   // 发FIN，优雅断开
            if (socket->state() != QAbstractSocket::UnconnectedState) {
                socket->waitForDisconnected(1000); // 最多等1秒
            }
        }
    }
}

void TcpClient::uploadFile(const QString &filePath)
{
    QFileInfo info(filePath);
    if (!info.exists() || !info.isFile()) {
        emit uploadComplete(false);
        return;
    }

    file = new QFile(filePath, this);
    if (!file->open(QIODevice::ReadOnly)) {
        emit uploadComplete(false);
        return;
    }

    uploadFileId = QRandomGenerator::global()->bounded(100000) + 1;
    uploadTotalChunks = (file->size() + CHUNK_SIZE - 1) / CHUNK_SIZE;
    currentChunk = 0;

    qDebug() << "准备上传:" << info.fileName()
             << "大小:" << file->size()
             << "块数:" << uploadTotalChunks;

    // 构建上传请求（放在 ChatMsg.content 里）
    int chunkHeaderSize = sizeof(FileChunk);
    FileChunk *chunk = (FileChunk*)malloc(chunkHeaderSize);
    memset(chunk, 0, chunkHeaderSize);

    chunk->fileId = uploadFileId;
    chunk->chunkIndex = 0;  // 请求时填0
    chunk->chunkSize = 0;   // 请求时填0
    chunk->totalChunks = uploadTotalChunks;
    chunk->fileSize = file->size();
    strncpy(chunk->fileName, info.fileName().toUtf8().constData(), 128);


    sendFileMessage(QByteArray((char*)chunk, chunkHeaderSize), 6);

    free(chunk);
}



void TcpClient::onConnected()
{
    // qDebug() << "已连接到服务器";
    // sendMessage("Hello Server!"); // 连接成功后自动发送消息

    emit qq_connected();
}

void TcpClient::onDisconnected()
{

    socket->close();
    qDebug() << "已断开连接";
}

void TcpClient::onReadyRead()
{
    //qDebug()<<"开始读:";
    int len=socket->bytesAvailable();
    while(len>=8){
        char tembuffer[100];
        int total_len=0;
        socket->read(tembuffer,sizeof(total_len));
        // if(len<=0){
        //     if(errno==EAGAIN || errno == EWOULDBLOCK)
        //     continue;//数据暂时读完了
        //     else  {
        //         return;
        //     }
        // }
        //else{
        total_len=*(int*) tembuffer;
        char* buffer = (char*)malloc(total_len);
        memcpy(buffer, tembuffer, 4); // 将已经读取的4字节复制到buffer开头
        ChatMsg* message;
        socket->read(buffer+4,total_len-4);
        message=(ChatMsg*)buffer;
        //qDebug()<<"消息类型:"<<message->type;
        //message->content[total_len-8]='\0';
        if(message->type==0){
            int length=strlen(message->content);
            qDebug()<<"长度:"<<length;
            qDebug()<<"收到:"<<message->content;

            //printf("收到:%s",message->content);
        }
        if(message->type==1){
            int contentLen = message->totalLen - sizeof(ChatMsg);
            QString userListStr = QString::fromUtf8(message->content,contentLen);
            //qDebug()<<"userlist:\n"<<userListStr;
            QStringList users = userListStr.split("\n", Qt::SkipEmptyParts);
            emit qq_userlist(users);

        }
        if(message->type==2){
            //qDebug()<<"已收到";
            //qDebug()<<"收到："<<message->content<<"总长度:"<<message->totalLen;
            int contentLen = message->totalLen - sizeof(ChatMsg);
            QString msgText = QString::fromUtf8(message->content, contentLen);
            //message->content[message->totalLen-8]='\0';
            emit qq_recvmsg(msgText);
        }
        if(message->type==6){           
            FileChunk *fheader = (FileChunk*)(message->content);
            QString status = QString::fromUtf8(fheader->fileName);
            qDebug() << "文件传输响应状态：" << status;

            if (status == "PUSH_FILE") {
                // 服务器推送文件，开始下载
                qDebug() << "开始接收文件:" << downloadFileName;

                // 创建下载目录
                QString saveDir = QCoreApplication::applicationDirPath() + "/downloads/";
                QDir().mkpath(saveDir);
                QString savePath = saveDir + downloadFileName;

                downloadFile = new QFile(savePath, this);
                if (downloadFile->open(QIODevice::WriteOnly)) {
                    downloadFileId = fheader->fileId;
                    downloadTotalChunks = fheader->totalChunks;
                    downloadCurrentChunk = 0;
                    //downloadFileName = QString::fromUtf8(fheader->fileName);

                    qDebug() << "开始下载:" << savePath
                             << "大小:" << fheader->fileSize
                             << "块数:" << downloadTotalChunks;
                } else {
                    qDebug() << "创建文件失败:" << savePath;
                    emit downloadComplete(false, "");
                }
            }
            else if (status == "ACK") {
                if (file && uploadTotalChunks > 0) {
                    qDebug() << "服务器允许上传，开始发送数据";
                    sendNextChunk();
                }
            }
            else if (status == "ERROR") {
                if (file) {
                    file->close();
                    file->deleteLater();
                    file = nullptr;
                    emit uploadComplete(false);
                }
                if (downloadFile) {
                    downloadFile->close();
                    downloadFile->deleteLater();
                    downloadFile = nullptr;
                    emit downloadComplete(false, "");
                }
            }
            else if (status == "COMPLETE") {
                if (file) {
                    qDebug() << "上传完成";
                    file->close();
                    file->deleteLater();
                    file = nullptr;
                    uploadTotalChunks = 0;
                    emit uploadComplete(true);
                }
                if (downloadFile) {
                    qDebug() << "下载完成:" << downloadFileName;
                    QString filePath = downloadFile->fileName();
                    downloadFile->close();
                    downloadFile->deleteLater();
                    downloadFile = nullptr;
                    emit downloadComplete(true, filePath);
                }
            }
            else {
                // 文件数据块
                if (downloadFile && fheader->fileId == downloadFileId) {
                    // 接收下载数据
                    downloadFile->write(fheader->data, fheader->chunkSize);
                    downloadCurrentChunk++;

                    int percent = downloadCurrentChunk * 100 / downloadTotalChunks;
                    emit downloadProgress(percent);

                    qDebug() << "接收下载块" << fheader->chunkIndex << "/" << downloadTotalChunks;
                }
                else if (file && uploadTotalChunks > 0) {
                    // 上传进度确认
                    currentChunk = fheader->chunkIndex + 1;
                    if (currentChunk < uploadTotalChunks) {
                        sendNextChunk();
                    }
                }
            }
        }//type==6
        if(message->type==9){//获取文件列表
            QString fileListStr = QString::fromUtf8(message->content);
            //qDebug()<<"收到文件列表";
            //qDebug()<<message->content;
            if (fileListStr == "暂无可用文件") {
                emit fileListReceived(QStringList());  // 空列表
            } else {
                // 按换行分割，过滤空行
                QStringList files = fileListStr.split("\n", Qt::SkipEmptyParts);
                emit fileListReceived(files);
            }
        }
        free(buffer);
        len = socket->bytesAvailable();
        //}
    }//while

    //QByteArray data = socket->readAll();

    //socket->read(buffer,sizeof(buffer));
    //qDebug() << "收到:" << QString::fromUtf8(data);
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    emit qq_disconnected();
    //qDebug() << "错误:" << socket->errorString();
}

void TcpClient::sendNextChunk()
{
    if (!file || currentChunk >= uploadTotalChunks) return;

    qint64 offset = (qint64)currentChunk * CHUNK_SIZE;
    file->seek(offset);

    QByteArray fileData = file->read(CHUNK_SIZE);
    int chunkLen = fileData.size();

    // 构建 FileChunk + 数据
    int totalContentLen = sizeof(FileChunk) + chunkLen;
    FileChunk *chunk = (FileChunk*)malloc(totalContentLen);
    memset(chunk, 0, totalContentLen);

    chunk->fileId = uploadFileId;
    chunk->chunkIndex = currentChunk;
    chunk->chunkSize = chunkLen;
    chunk->totalChunks = uploadTotalChunks;
    chunk->fileSize = file->size();
    // fileName
    memcpy(chunk->data, fileData.constData(), chunkLen);

    // 用 sendFileMessage 发送（type=6）
    sendFileMessage(QByteArray((char*)chunk, totalContentLen), 6);

    free(chunk);

    int percent = (currentChunk + 1) * 100 / uploadTotalChunks;
    emit uploadProgress(percent);

    qDebug() << "发送块" << currentChunk << "/" << uploadTotalChunks;
}

void TcpClient::requestDownloadFile(int fileId,QString filename)
{
    // 构建下载请求消息
    int totalLen = sizeof(ChatMsg) + sizeof(int);
    downloadFileName=filename;
    ChatMsg* msg = (ChatMsg*)malloc(totalLen);
    msg->totalLen = totalLen;
    msg->type = 8;  // 文件下载请求
    memcpy(msg->content, &fileId, sizeof(int));

    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write((const char*)msg, totalLen);
        qDebug() << "请求下载文件 ID:" << fileId;
    } else {
        qDebug() << "未连接到服务器";
    }

    free(msg);
}

void TcpClient::sendFileMessage(const QByteArray &content, int type)
{
    //qDebug()<<"发送头部";
    int contentLen = content.size();
    int totalLen = sizeof(ChatMsg) + contentLen;

    ChatMsg *msg = (ChatMsg*)malloc(totalLen);
    msg->totalLen = totalLen;
    msg->type = type;
    memcpy(msg->content, content.constData(), contentLen);
   // msg->content[contentLen] = '\0';

    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write((const char*)msg, totalLen);
        qDebug()<<"发送头部成功";
    }

    free(msg);
}
