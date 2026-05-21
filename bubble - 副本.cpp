#include "Bubble.h"
#include<QDebug>
Bubble::Bubble(const QString &text, bool isSelf, QWidget *parent)
    : QLabel(parent)
{
    // if(isSelf){
    // setText(text);
    // }
    // else{

    // }
    setText(text);
    initStyle(isSelf);

    // 设置合适的大小

    setMaximumWidth(280);


    // //计算并设置最小高度
    // QFontMetrics fm(font());
    // QRect bound = fm.boundingRect(QRect(0, 0, 250, 10000),
    //                               Qt::AlignLeft | Qt::TextWordWrap,
    //                               text);

    // setMinimumSize(bound.width() + 24, bound.height() + 16);

    // 用 sizeHint 获取 QLabel 自己计算的大小（包含 wordWrap）
    QSize sh = sizeHint();

    // 加上 padding 的额外空间（样式表 padding: 8px 12px）
    int finalW = sh.width() + 24;   // 左右 padding 12*2
    int finalH = sh.height();  // 上下

    // 限制宽度不超过气泡最大宽度
    finalW = qMin(finalW, 280);

    setFixedSize(finalW, finalH);  //固定大小

    // qDebug() << "文本:" << text << "sizeHint:" << sizeHint()
    //         << "finalSize:" << QSize(finalW, finalH);
    //adjustBubbleSize();
}

void Bubble::initStyle(bool isSelf)
{
    // 开启自动换行
    setWordWrap(true);
    // 限制气泡最大宽度，超过自动换行
    setMaximumWidth(280);

    if (isSelf)
    {
        // 自己：绿色气泡
        setStyleSheet(R"(
            QLabel{
                background-color:#95EC69;
                border-radius:12px;
                padding:8px 12px;
                color:#333333;
                font-size:12px;
            }
        )");
    }
    else
    {
        // 别人：灰色气泡
        setStyleSheet(R"(
            QLabel{
                background-color:#F5F5F5;
                border-radius:12px;
                padding:8px 12px;
                color:#333333;
                font-size:12px;
            }
        )");
    }
}

void Bubble::adjustBubbleSize()
{
    {
        // 根据文字自动适配气泡宽高
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        adjustSize();
    }       // 自动适配气泡大小
}

