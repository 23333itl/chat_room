#ifndef CHAT_ROOM_H
#define CHAT_ROOM_H

#include <QWidget>
#include<QTimer>
#include<QMouseevent>
#include <QAbstractAnimation>
#include<QKeyEvent>
#include<QListWidgetItem>
#include"tcp_demo.h"
#pragma pack(push, 1)
#include "protocol.h"
#pragma pack(pop)
namespace Ui {
class chat_room;
}

class chat_room : public QWidget
{
    Q_OBJECT

protected:
    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event) override;//用于enter发送消息
public:
    explicit chat_room(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void addmember(QString &name);
    ~chat_room();
    QTimer* gettimer();
    void addMessage(const QString& text, bool isMe);
    void setfilesta(bool success);
    void setfilepro(int percent);
    void updateUserList(QStringList users);
    void updateFileList(QStringList files);
    QString formatFileSize(quint64 size);//字节转KB,GB
    void onDownloadProgress(int percent);
    void onDownloadComplete(bool success, QString filePath);
    void setusername(QString name);
private slots:
    void on_btn_member_clicked();

    void on_btn_doc_clicked();

    void toggleRightPanel();  // 收起/展开

    void on_btn_send_clicked();
    void on_btn_file_clicked();


    void on_listWidget_doc_itemDoubleClicked(QListWidgetItem *item);

    void on_btn_close_clicked();





signals:
     void sendmessage(const QString &msg);
    void uploadfile(const QString& filePath);
     void requestDownload(int fileid,const QString& filename);

private:
    Ui::chat_room *ui;
    QTimer* ping_timer;//测试连通性定时器
    QPoint mr_pos;
    QStringList member;//存储聊天室所有成员
    const int PANEL_WIDTH = 170;  // 右侧展开宽度
    bool isPanelVisible = true;   // 当前状态
    QAbstractAnimation *anim = nullptr;
    struct FileItemInfo {
        int fileId;
        QString fileName;
        qint64 fileSize;
    };
    QVector<FileItemInfo> currentFiles;  // 存储当前文件列表
    //TcpClient* client;

};

#endif // CHAT_ROOM_H
