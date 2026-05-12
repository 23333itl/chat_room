/********************************************************************************
** Form generated from reading UI file 'chat_room.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_ROOM_H
#define UI_CHAT_ROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chat_room
{
public:
    QWidget *widget_left;
    QPushButton *btn_send;
    QPushButton *btn_close;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lb_title;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *lb_name;
    QToolButton *btn_info;
    QFrame *line;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QFrame *line_3;
    QTextEdit *text_input;
    QPushButton *btn_file;
    QProgressBar *progressBar;
    QLabel *lb_status;
    QWidget *widget_right;
    QWidget *widget_tabBar;
    QToolButton *btn_member;
    QToolButton *btn_doc;
    QStackedWidget *stackedWidget;
    QWidget *page_member;
    QListWidget *listWidget_member;
    QFrame *line_4;
    QWidget *page_doc;
    QListWidget *listWidget_doc;
    QFrame *line_2;

    void setupUi(QWidget *chat_room)
    {
        if (chat_room->objectName().isEmpty())
            chat_room->setObjectName("chat_room");
        chat_room->resize(550, 420);
        chat_room->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color: rgb(255,255,255);\n"
"}"));
        widget_left = new QWidget(chat_room);
        widget_left->setObjectName("widget_left");
        widget_left->setGeometry(QRect(0, 0, 380, 420));
        btn_send = new QPushButton(widget_left);
        btn_send->setObjectName("btn_send");
        btn_send->setGeometry(QRect(270, 390, 50, 20));
        btn_send->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);\n"
"border-radius: 4px;"));
        btn_close = new QPushButton(widget_left);
        btn_close->setObjectName("btn_close");
        btn_close->setGeometry(QRect(330, 390, 50, 20));
        btn_close->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);\n"
"border-radius: 4px;"));
        layoutWidget = new QWidget(widget_left);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 381, 381));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lb_title = new QLabel(layoutWidget);
        lb_title->setObjectName("lb_title");
        QFont font;
        font.setPointSize(18);
        lb_title->setFont(font);
        lb_title->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);"));
        lb_title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lb_title);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lb_name = new QLabel(layoutWidget);
        lb_name->setObjectName("lb_name");

        horizontalLayout->addWidget(lb_name);

        btn_info = new QToolButton(layoutWidget);
        btn_info->setObjectName("btn_info");
        QFont font1;
        font1.setBold(true);
        btn_info->setFont(font1);
        btn_info->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background: rgb(153, 255, 51);\n"
"    border-radius: 16px;\n"
"    color: #000000;\n"
"    font-size: 9px;\n"
"    font-weight: bold;\n"
"}\n"
"QToolButton:hover {\n"
"    background: rgb(51,255,255);\n"
"}\n"
"QToolButton:pressed {\n"
"    background: rgb(255,0,127);\n"
"}"));
        btn_info->setToolButtonStyle(Qt::ToolButtonTextOnly);

        horizontalLayout->addWidget(btn_info);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(layoutWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        scrollArea = new QScrollArea(layoutWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMaximumSize(QSize(16777215, 248));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 377, 246));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        text_input = new QTextEdit(layoutWidget);
        text_input->setObjectName("text_input");
        text_input->setMaximumSize(QSize(16777215, 60));

        verticalLayout->addWidget(text_input);

        btn_file = new QPushButton(widget_left);
        btn_file->setObjectName("btn_file");
        btn_file->setGeometry(QRect(5, 385, 30, 30));
        btn_file->setStyleSheet(QString::fromUtf8("image: url(:/images/image_file.png);"));
        progressBar = new QProgressBar(widget_left);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(40, 390, 120, 20));
        progressBar->setValue(0);
        lb_status = new QLabel(widget_left);
        lb_status->setObjectName("lb_status");
        lb_status->setGeometry(QRect(180, 390, 85, 20));
        lb_status->setStyleSheet(QString::fromUtf8("color: #666;"));
        widget_right = new QWidget(chat_room);
        widget_right->setObjectName("widget_right");
        widget_right->setGeometry(QRect(380, 0, 170, 420));
        widget_right->setMaximumSize(QSize(16777215, 420));
        widget_tabBar = new QWidget(widget_right);
        widget_tabBar->setObjectName("widget_tabBar");
        widget_tabBar->setGeometry(QRect(0, 0, 170, 50));
        btn_member = new QToolButton(widget_tabBar);
        btn_member->setObjectName("btn_member");
        btn_member->setGeometry(QRect(5, 5, 80, 40));
        btn_member->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btn_doc = new QToolButton(widget_tabBar);
        btn_doc->setObjectName("btn_doc");
        btn_doc->setGeometry(QRect(85, 5, 80, 40));
        btn_doc->setToolButtonStyle(Qt::ToolButtonTextOnly);
        stackedWidget = new QStackedWidget(widget_right);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 54, 170, 366));
        page_member = new QWidget();
        page_member->setObjectName("page_member");
        listWidget_member = new QListWidget(page_member);
        listWidget_member->setObjectName("listWidget_member");
        listWidget_member->setGeometry(QRect(0, 0, 170, 366));
        listWidget_member->setStyleSheet(QString::fromUtf8("font: 9pt \"SimHei\";"));
        line_4 = new QFrame(page_member);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(0, 0, 170, 2));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        stackedWidget->addWidget(page_member);
        page_doc = new QWidget();
        page_doc->setObjectName("page_doc");
        listWidget_doc = new QListWidget(page_doc);
        listWidget_doc->setObjectName("listWidget_doc");
        listWidget_doc->setGeometry(QRect(0, 0, 170, 366));
        line_2 = new QFrame(page_doc);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 0, 170, 2));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        stackedWidget->addWidget(page_doc);

        retranslateUi(chat_room);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(chat_room);
    } // setupUi

    void retranslateUi(QWidget *chat_room)
    {
        chat_room->setWindowTitle(QCoreApplication::translate("chat_room", "\350\201\212\345\244\251\345\256\244", nullptr));
        btn_send->setText(QCoreApplication::translate("chat_room", "\345\217\221\351\200\201", nullptr));
        btn_close->setText(QCoreApplication::translate("chat_room", "\345\205\263\351\227\255", nullptr));
        lb_title->setText(QCoreApplication::translate("chat_room", "\350\201\212\345\244\251\345\256\244", nullptr));
        lb_name->setText(QCoreApplication::translate("chat_room", "TextLabel", nullptr));
        btn_info->setText(QCoreApplication::translate("chat_room", ">>", nullptr));
        btn_file->setText(QString());
        lb_status->setText(QCoreApplication::translate("chat_room", "\344\270\212\344\274\240\347\212\266\346\200\201", nullptr));
        btn_member->setText(QCoreApplication::translate("chat_room", "\347\276\244\350\201\212\346\210\220\345\221\230", nullptr));
        btn_doc->setText(QCoreApplication::translate("chat_room", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chat_room: public Ui_chat_room {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_ROOM_H
