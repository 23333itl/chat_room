#include "chat_login.h"
#include "ui_chat_login.h"
#include <QVBoxLayout>
#include <QRegularExpressionValidator>
chat_login::chat_login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chat_login)
{
    ui->setupUi(this);
    connect_timer =new QTimer(this);
    connect_timer->setSingleShot(true);//只触发一次
    client_login=new TcpClient(this);
    QTcpSocket* sock=client_login->getsocket();
    //初始化UI布局
    //创建垂直布局
    ui->btn_reg->hide();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(ui->CentralWidget, 1);
    QPixmap pix(":/images/image_QQ.jpg");
    ui->lb_QQ->setPixmap(
        pix.scaled(
            ui->lb_QQ->size(),
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            )
        );
    //设置无边框窗口
    setWindowFlag(Qt::FramelessWindowHint);
    //固定窗口大小
    setFixedSize(width(),height());
    //右键菜单设置
    exitmenu =new QMenu(this);
    exitact=new QAction;
    exitact->setText(u8"退出");
    exitact->setIcon(QIcon(":/images/close.ico"));
    exitmenu->addAction(exitact);
    //状态栏
    sta=new QStatusBar(this);
    sta->showMessage("欢迎使用QQ聊天室山寨版1.0");
    sta->setStyleSheet("background-color: rgba(0,0,0,20); color: white; font-size: 9pt; border-top: 1px solid rgba(255,255,255,50);");
    mainLayout->addWidget(sta);

    // 只允许 字母 + 数字，不能输入中文
    QRegularExpression reg("^[a-zA-Z0-9]+$");
    QValidator *validator = new QRegularExpressionValidator(reg, this);
    ui->edt_password->setValidator(validator);
    //信号与槽连接
    connect(exitact,SIGNAL(triggered(bool)),this,SLOT(slot_exitApp()));


}

QTimer *chat_login::gettimer()
{
    return connect_timer;
}

void chat_login::set_stainfo(QString message)
{
    sta->clearMessage();
    sta->showMessage(message);
}

QString chat_login::getname()
{
    qDebug()<<"用户名:"<<ui->edt_name->text();
    return ui->edt_name->text();
}

QString chat_login::getpassword()
{
    return ui->edt_password->text();
}

chat_login::~chat_login()
{
    delete ui;
}

void chat_login::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos()-m_pos);

}

void chat_login::mousePressEvent(QMouseEvent *event)
{
     m_pos=event->pos();
}

void chat_login::contextMenuEvent(QContextMenuEvent *event)
{
    exitmenu->exec(QCursor::pos());
    event->accept();
}

void chat_login::slot_exitApp()
{
    qApp->exit(0);
}




void chat_login::on_btn_login_clicked()
{
    //qDebug()<<"qq_login信号发出";

    emit qq_login();
}

