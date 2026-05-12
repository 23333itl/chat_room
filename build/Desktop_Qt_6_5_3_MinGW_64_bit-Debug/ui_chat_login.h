/********************************************************************************
** Form generated from reading UI file 'chat_login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_LOGIN_H
#define UI_CHAT_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chat_login
{
public:
    QWidget *CentralWidget;
    QLabel *lb_QQ;
    QLabel *label;
    QLineEdit *edt_name;
    QLabel *label_2;
    QLineEdit *edt_password;
    QPushButton *btn_login;
    QPushButton *btn_reg;

    void setupUi(QWidget *chat_login)
    {
        if (chat_login->objectName().isEmpty())
            chat_login->setObjectName("chat_login");
        chat_login->resize(542, 420);
        chat_login->setStyleSheet(QString::fromUtf8("QWidget{\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:0, \n"
"            stop:0 #64B5F6, stop:1 #F093FB);\n"
"        border: none;\n"
"}"));
        CentralWidget = new QWidget(chat_login);
        CentralWidget->setObjectName("CentralWidget");
        CentralWidget->setGeometry(QRect(6, 6, 531, 371));
        lb_QQ = new QLabel(CentralWidget);
        lb_QQ->setObjectName("lb_QQ");
        lb_QQ->setGeometry(QRect(200, 20, 121, 91));
        lb_QQ->setAlignment(Qt::AlignCenter);
        label = new QLabel(CentralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 190, 61, 31));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        edt_name = new QLineEdit(CentralWidget);
        edt_name->setObjectName("edt_name");
        edt_name->setGeometry(QRect(260, 190, 121, 31));
        edt_name->setStyleSheet(QString::fromUtf8("border: none;\n"
"    border-radius: 6px;\n"
"    padding: 8px 12px;\n"
"    font-size:14px;\n"
"    color:#333;"));
        label_2 = new QLabel(CentralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 250, 61, 31));
        QFont font1;
        font1.setPointSize(14);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        edt_password = new QLineEdit(CentralWidget);
        edt_password->setObjectName("edt_password");
        edt_password->setGeometry(QRect(260, 250, 121, 31));
        edt_password->setStyleSheet(QString::fromUtf8("border: none;\n"
"    border-radius: 6px;\n"
"    padding: 8px 12px;\n"
"    font-size:14px;\n"
"    color:#333;"));
        edt_password->setEchoMode(QLineEdit::Password);
        btn_login = new QPushButton(CentralWidget);
        btn_login->setObjectName("btn_login");
        btn_login->setGeometry(QRect(180, 320, 56, 18));
        btn_login->setStyleSheet(QString::fromUtf8("\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    font-size: 9pt;\n"
"    color: #333333;\n"
"    padding: 2px 6px;"));
        btn_reg = new QPushButton(CentralWidget);
        btn_reg->setObjectName("btn_reg");
        btn_reg->setGeometry(QRect(290, 320, 56, 18));
        btn_reg->setStyleSheet(QString::fromUtf8("\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    font-size: 9pt;\n"
"    color: #333333;\n"
"    padding: 2px 6px;"));

        retranslateUi(chat_login);

        QMetaObject::connectSlotsByName(chat_login);
    } // setupUi

    void retranslateUi(QWidget *chat_login)
    {
        chat_login->setWindowTitle(QCoreApplication::translate("chat_login", "Form", nullptr));
        lb_QQ->setText(QString());
        label->setText(QCoreApplication::translate("chat_login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("chat_login", "\345\257\206\347\240\201", nullptr));
        btn_login->setText(QCoreApplication::translate("chat_login", "\347\231\273\345\275\225", nullptr));
        btn_reg->setText(QCoreApplication::translate("chat_login", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chat_login: public Ui_chat_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_LOGIN_H
