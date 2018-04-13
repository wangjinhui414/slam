#include "logindialog.h"
#include "ui_logindialog.h"
#include "databasedata.h"
#include <QMessageBox>
#include "memdata.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    int ret = g_comser.Login(ui->usrlineEdit->text().trimmed(),ui->pwdlineEdit->text().trimmed());
    ret = 1;
    if(ret == 1)
    {
       //登录成功，则触发accept函数
       accept();
    }
    else if(ret == -1)
    {
       //登录失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
       QMessageBox::warning(this,QStringLiteral("警告！"),QStringLiteral("用户名或者密码错误！"),QMessageBox::Ok);
       ui->usrlineEdit->clear();//清空用户编辑框
       ui->pwdlineEdit->clear();
       ui->usrlineEdit->setFocus();//设置光标到用户编辑框
    }
    else if(ret == 0)
    {
        QMessageBox::warning(this,QStringLiteral("警告！"),QStringLiteral("服务器无响应"),QMessageBox::Ok);
    }

}
