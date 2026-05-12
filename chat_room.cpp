#include "chat_room.h"
#include "ui_chat_room.h"
#include <QHBoxLayout>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSizePolicy>
#include <QScrollBar>
#include"bubble.h"
#include <QFileDialog>
#include<QMessageBox>
#include<QFont>
chat_room::chat_room(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chat_room)
    , anim(nullptr)
{
    ui->setupUi(this);
    //初始化UI
    //固定窗口大小
    setFixedSize(width(), height());
    ping_timer = new QTimer(this);
    ui->text_input->installEventFilter(this);
    // client=new TcpClient(this);
    // QTcpSocket* sock=client->getsocket();
    // 根水平布局：左侧随右侧宽度变化自动占满剩余空间
    auto *rootLay = new QHBoxLayout(this);
    rootLay->setContentsMargins(0, 0, 0, 0);
    rootLay->setSpacing(0);
    rootLay->addWidget(ui->widget_left, 1);
    rootLay->addWidget(ui->widget_right, 0);

    ui->widget_left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui->widget_right->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    ui->widget_right->setMinimumWidth(PANEL_WIDTH);
    ui->widget_right->setMaximumWidth(PANEL_WIDTH);

    ui->stackedWidget->setCurrentIndex(0);//默认显示群聊成员
    //测试数据
    // 成员列表
    QFont font("Microsoft YaHei", 9);
    ui->listWidget_member->setFont(font);
    ui->listWidget_member->addItem("🟢 老秦");
    ui->listWidget_member->addItem("🟢 秦先生");
    member={};
    //ui->listWidget_member->addItem("⚫ 离线用户");

    // 文件列表
    ui->listWidget_doc->addItem("📁 设计稿.zip");
    ui->listWidget_doc->addItem("📦 少年派.zip");

    // 右侧展开时：按钮表示可收起
    ui->btn_info->setText("<<");

    //聊天区
    // 获取 scrollArea 里的垂直布局
    QVBoxLayout *msgLayout = qobject_cast<QVBoxLayout*>(
        ui->scrollAreaWidgetContents->layout()
        );

    // // 创建消息气泡
    // QLabel *bubble = new QLabel("你好！", ui->scrollAreaWidgetContents);
    // bubble->setStyleSheet("    background-color: #F5F5F5;"
    //                       "border-radius: 12px;padding: 8px 12px;color: #333333;"
    //                       "font-size: 12px;max-width: 220px;"
    //                       "qproperty-wordWrap: true;border: none;");
    // bubble->setWordWrap(true);
    // bubble->setMaximumWidth(300);
    Bubble*  bubble=new Bubble("你好",false,this);
    Bubble*  bubble2=new Bubble("我不好",true,this);

    // 插入到弹簧之前（弹簧是最后一个 item）
    int spacerIndex = msgLayout->count() - 1;
    msgLayout->insertWidget(spacerIndex, bubble,0,Qt::AlignLeft);
    spacerIndex = msgLayout->count() - 1;
    msgLayout->insertWidget(spacerIndex, bubble2,0,Qt::AlignRight);
    //msgLayout->addWidget(bubble,0,Qt::AlignLeft);


    // 滚动到底部
    QScrollBar *bar = ui->scrollArea->verticalScrollBar();
    bar->setValue(bar->maximum());


    //信号与槽连接
    connect(ui->btn_info, &QToolButton::clicked, this, &chat_room::toggleRightPanel);
    connect(bar, &QScrollBar::rangeChanged, bar, [=](){
        bar->setValue(bar->maximum());
        // 执行一次后断开连接，避免后续滚动被强制拉走
        disconnect(bar, &QScrollBar::rangeChanged, this, nullptr);
    });

    // QObject::connect(client, &TcpClient::uploadProgress, this, [=](int percent){
    //     chat->progressBar->setValue(percent);
    // });




}

void chat_room::mouseMoveEvent(QMouseEvent *event)
{
     move(event->globalPos()-mr_pos);
}

void chat_room::mousePressEvent(QMouseEvent *event)
{
     mr_pos=event->pos();
}

//将服务器发来的新的成员加入之后显示
void chat_room::addmember(QString &name)
{

    //member<<name;
    ui->listWidget_member->addItem(QString("🟢 %1").arg(name));
}



chat_room::~chat_room()
{
    if (anim) {
        anim->stop();
        delete anim;
        anim = nullptr;
    }
    delete ui;
}

QTimer *chat_room::gettimer()
{
    return ping_timer;
}

void chat_room::addMessage(const QString &text, bool isMe)
{
    // 创建气泡
    Bubble *bubble = new Bubble(text, isMe, this);

    // 获取布局
    QVBoxLayout *msgLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    //  插入到弹簧前面
    int spacerIndex = msgLayout->count() - 1;

    //  自己的消息靠右，别人的靠左
    if(isMe) {
        msgLayout->insertWidget(spacerIndex, bubble, 0, Qt::AlignRight);
    } else {
        msgLayout->insertWidget(spacerIndex, bubble, 0, Qt::AlignLeft);
    }

    //更新布局
    ui->scrollAreaWidgetContents->adjustSize();

    //滚动到底部
    QTimer::singleShot(50, this, [this]() {
        QScrollBar *bar = ui->scrollArea->verticalScrollBar();
        bar->setValue(bar->maximum());
    });

}


void chat_room::setfilesta(bool success)
{
    if (success) {
                ui->lb_status->setText("上传成功");
                QMessageBox::information(this, "完成", "文件上传成功");
            } else {
                ui->lb_status->setText("上传失败");
                QMessageBox::warning(this, "错误", "文件上传失败");
            }
            ui->btn_file->setEnabled(true);
}

void chat_room::setfilepro(int percent)
{
    ui->progressBar->setValue(percent);
}

void chat_room::updateUserList(QStringList users)
{
    //user:新的成员列表，member:旧的成员列表
    ui->listWidget_member->clear();  // 清空现有列表
    // if(member.empty()){
    //     member=users;
    // }

    for (QString& user : users) {
        addmember(user);
    }
    // 第一次收到列表（member为空），只更新列表，不显示系统消息
    if (member.isEmpty()) {
        member = users;
        return;
    }
    QSet<QString> old(member.begin(),member.end());
    QSet<QString> new_list(users.begin(),users.end());
    QSet<QString> mem_leave=old;
    QSet<QString> mem_join=new_list;
    mem_leave.subtract(new_list);//只在member里，离开聊天室的人
    mem_join.subtract(old); //只在users里，加入聊天室的人
    qDebug()<<"member:"<<member;
    qDebug()<<"users:"<<users;
    qDebug()<<"mem_leave:"<<mem_leave;
    qDebug()<<"mem_join:"<<mem_join;
    qDebug()<<"\n";
    if(!mem_leave.empty()){//有人离开
        qDebug()<<"有人离开";
        for(auto& leave:mem_leave){
            // 创建系统消息mem
            QLabel* sys_message=new QLabel;
            sys_message->setText(QString("%1 离开了聊天室").arg(leave));
            // 获取布局
            QVBoxLayout *msgLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

            //  插入到弹簧前面
            int spacerIndex = msgLayout->count() - 1;

            msgLayout->insertWidget(spacerIndex,sys_message,0,Qt::AlignHCenter);
        }
    }
    if(!mem_join.empty()){//有人加入
        qDebug()<<"有人加入";
        for(auto& join:mem_join){
        // 创建系统消息
        QLabel* sys_message=new QLabel;
        sys_message->setText(QString("%1 加入了聊天室").arg(join));
        // 获取布局
        QVBoxLayout *msgLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

        //  插入到弹簧前面
        int spacerIndex = msgLayout->count() - 1;

        msgLayout->insertWidget(spacerIndex,sys_message,0,Qt::AlignHCenter);
        }
    }
    member=users;
}

void chat_room::updateFileList(QStringList files)
{
    ui->listWidget_doc->clear();
    //files:文件ID|文件名|文件大小(字节)
    for (const QString& file :files) {
        QStringList parts = file.split("|");
        if(parts[0]=="暂无可用文件"){
            ui->listWidget_doc->addItem("暂无可用文件");
            break;
        }
        if (parts.size() >= 3) {
            int fileId = parts[0].toInt();
            QString fileName = parts[1];
            qint64 fileSize = parts[2].toLongLong();

            // 存储文件信息（包含fileId）
            FileItemInfo info;
            info.fileId = fileId;      // 新增
            info.fileName = fileName;
            info.fileSize = fileSize;
            currentFiles.append(info);

            // 格式化文件大小显示
            QString sizeStr = formatFileSize(fileSize);

            // 添加到文件列表显示
            ui->listWidget_doc->addItem(
                QString("📁 %1\n   大小: %2")
                    .arg(fileName)
                    .arg(sizeStr)
                );
        }
    }
}

QString chat_room::formatFileSize(quint64 size)
{
    if (size > 1024 * 1024) {
        return QString::number(size / (1024.0 * 1024.0), 'f', 2) + " MB";
    } else if (size > 1024) {
        return QString::number(size / 1024.0, 'f', 2) + " KB";
    } else {
        return QString::number(size) + " B";
    }
}

void chat_room::on_btn_member_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    //showmember();
}


void chat_room::on_btn_doc_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void chat_room::toggleRightPanel()
{
    if (anim)
        return;

    const int startW = ui->widget_right->width();
    const int endW = isPanelVisible ? 0 : PANEL_WIDTH;

    auto *group = new QParallelAnimationGroup();
    auto *animMin = new QPropertyAnimation(ui->widget_right, "minimumWidth", group);
    auto *animMax = new QPropertyAnimation(ui->widget_right, "maximumWidth", group);
    animMin->setDuration(200);
    animMax->setDuration(200);
    animMin->setEasingCurve(QEasingCurve::InOutQuad);
    animMax->setEasingCurve(QEasingCurve::InOutQuad);
    animMin->setStartValue(startW);
    animMin->setEndValue(endW);
    animMax->setStartValue(startW);
    animMax->setEndValue(endW);

    group->addAnimation(animMin);
    group->addAnimation(animMax);

    const bool collapsing = isPanelVisible;
    connect(group, &QParallelAnimationGroup::finished, this, [this, collapsing, group]() {
        if (collapsing) {
            ui->widget_right->setMinimumWidth(0);
            ui->widget_right->setMaximumWidth(0);
            ui->btn_info->setText(">>");
            isPanelVisible = false;
        } else {
            ui->widget_right->setMinimumWidth(PANEL_WIDTH);
            ui->widget_right->setMaximumWidth(PANEL_WIDTH);
            ui->btn_info->setText("<<");
            isPanelVisible = true;
        }
        anim = nullptr;
        group->deleteLater();
    });

    anim = group;
    group->start();
}




void chat_room::on_btn_send_clicked()
{
    // 获取输入框文字
    QString msg = ui->text_input->toPlainText().trimmed();
    if(msg.isEmpty()) return;

    // 添加自己的消息（靠右）
    addMessage(msg, true);

    // 清空输入框
    ui->text_input->clear();
    //发送消息到服务器
    emit sendmessage(msg);
}

bool chat_room::eventFilter(QObject *obj, QEvent *event)
{
    // 只监听 textEdit 键盘按下
    if (obj == ui->text_input && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvt = static_cast<QKeyEvent*>(event);

        // 按下回车 且 没按Shift → 发送消息
        if (keyEvt->key() == Qt::Key_Return || keyEvt->key() == Qt::Key_Enter)
        {
            if (!keyEvt->modifiers().testFlag(Qt::ShiftModifier))
            {
                // 执行发送
                on_btn_send_clicked();
                // 拦截事件：不让回车换行
                return true;
            }
            // Shift+回车 不拦截，允许正常换行
        }
    }

    // 其他事件正常放行
    return QWidget::eventFilter(obj, event);
}

void chat_room::on_btn_file_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "*.*");
    if (!filePath.isEmpty()) {
        emit uploadfile(filePath);
       // client->uploadFile(filePath);
    }
}


void chat_room::on_listWidget_doc_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->listWidget_doc->row(item);
    if (index >= 0 && index < currentFiles.size()) {
        int fileid=currentFiles[index].fileId;
        QString fileName = currentFiles[index].fileName;
        qint64 fileSize = currentFiles[index].fileSize;

        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "下载文件",
            QString("确定要下载文件吗？\n\n文件名: %1\n大小: %2")
                .arg(fileName)
                .arg(formatFileSize(fileSize)),
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            // 发送下载请求，需要实现文件下载功能
            qDebug() << "请求下载文件:" << fileName;
             emit requestDownload(fileid,fileName);
        }
    }
}

//未实现
void chat_room::on_btn_close_clicked()
{

}

void chat_room::setusername(QString name)
{
    ui->lb_name->setText("当前用户:"+name);
}

void chat_room::onDownloadProgress(int percent) {
    ui->progressBar->setValue(percent);
    ui->lb_status->setText(QString("下载中... %1%").arg(percent));
}

void chat_room::onDownloadComplete(bool success, QString filePath) {
    if (success) {
        ui->lb_status->setText("下载完成");
        ui->progressBar->setValue(100);
        QMessageBox::information(this, "下载完成",
                                 QString("文件已保存到:\n%1").arg(filePath));
    } else {
        ui->lb_status->setText("下载失败");
        ui->progressBar->setValue(0);
        QMessageBox::warning(this, "错误", "文件下载失败");
    }
}
