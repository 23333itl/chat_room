#ifndef BUBBLE_H
#define BUBBLE_H

#include <QLabel>

class Bubble : public QLabel
{
    Q_OBJECT
public:
    // 构造：传入消息内容 + 是否自己的消息
    explicit Bubble(const QString &text, bool isSelf = false, QWidget *parent = nullptr);
    void initStyle(bool isSelf);    // 初始化气泡样式
    void adjustBubbleSize();
private:


};

#endif // BUBBLE_H
