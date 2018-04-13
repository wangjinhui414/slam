#include "slamconfig.h"
#include "ui_slamconfig.h"
#include <QMenu>
#include <QAction>


SlamConfig::SlamConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlamConfig)
{

    ui->setupUi(this);
    ui->pushButton_3->hide();
    ui->pushButton_2->hide();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("agvs");
    db.setUserName("root");
    db.setPassword("thunder865");
    if(!db.open())
    {
        //qDebug()<<"打开成功";
        QMessageBox::critical(NULL, QObject::tr("Collection"), QObject::tr("failed to connect to database!"));
    }
    SlamConfig::on_new_clicked();
    on_back_clicked();

}

SlamConfig::~SlamConfig()
{
    delete ui;
}


void SlamConfig::on_save_clicked()
{
    QSqlQuery query;
    query.prepare("insert into slaminfo (slamname,position,department,slamip,camip,camname,clientip,lidarip,navkitip,padip,status)values(:slamname ,:position,:department,:slamip,:camip,:camname,:clientip,:lidarip,:navkitip,:padip,0)");
    //以下合法性检测可改为lambda表达式的试进行优化，此处直接罗列
    QString input0 = ui->lineEdit_0->text();
    QString input2 = ui->lineEdit_2->text();
    QString input3 = ui->lineEdit_3->text();
    QString input4 = ui->lineEdit_4->text();
    QString input5 = ui->lineEdit_5->text();
    QString input6 = ui->lineEdit_6->text();
    QString input7 = ui->lineEdit_7->text();
    QString input8 = ui->lineEdit_8->text();
    QString input9 = ui->lineEdit_9->text();
    QString input10 = ui->lineEdit_10->text();
    if(input0.isEmpty())
    {
     QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("SLAM机器人名称不能为空，请检查!"));
    }
    else
    if(input2.isEmpty())
    {
     QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("存储位置不能为空，请检查!"));
    }
    else
        if(input3.isEmpty())
        {
         QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("所属部门不能为空，请检查!"));
        }
    else
        if(input4.isEmpty())
            {
             QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("SLAM机器人IP地址不能为空，请检查!"));
            }
        else
        if(input5.isEmpty())
        {
         QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("摄像头IP地址不能为空，请检查!"));
        }
        else
        if(input6.isEmpty())
        {
         QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("摄像头名称不能为空，请检查!"));
        }
        else
        if(input7.isEmpty())
        {
         QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("网络客户端IP地址不能为空，请检查!"));
        }
        else
        if(input8.isEmpty())
        {
         QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("激光雷达IP地址不能为空，请检查!"));
        }
        else
        if(input9.isEmpty())
        {
         QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("雷达控制板Navkit的IP地址不能为空，请检查!"));
        }
        else
        if(input10.isEmpty())
        {
         QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("车载平板电脑IP地址不能为空，请检查!"));
        }
//合法性检测结束。第处只检测了是否为空，其他的格式没有进行检测。
        else{
            query.bindValue(":slamname",ui->lineEdit_0->text());
            query.bindValue(":position",ui->lineEdit_2->text());
            query.bindValue(":department",ui->lineEdit_3->text());
            query.bindValue(":slamip",ui->lineEdit_4->text());
            query.bindValue(":camip",ui->lineEdit_5->text());
            query.bindValue(":camname",ui->lineEdit_6->text());
            query.bindValue(":clientip",ui->lineEdit_7->text());
            query.bindValue(":lidarip",ui->lineEdit_8->text());
            query.bindValue(":navkitip",ui->lineEdit_9->text());
            query.bindValue(":padip",ui->lineEdit_10->text());
            query.exec();
            select();
            QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("用户信息保存成功!"));
            ui->lineEdit_0->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_7->clear();
            ui->lineEdit_8->clear();
            ui->lineEdit_9->clear();
            ui->lineEdit_10->clear();
            ui->lineEdit_0->setFocus();
      }
}

void SlamConfig::on_new_clicked()
{
    ui->pushButton_3->show();
    ui->pushButton_2->show();
    ui->pushButton_4->hide();
    ui->pushButton->hide();
    ui->lineEdit_0->setFocus();
}

void SlamConfig::on_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, QStringLiteral("警告"),QStringLiteral("数据尚未保存，你确定要取消吗？"),
                                        QMessageBox::Yes | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)

        SlamConfig::close();//直接关闭

    if (reply == QMessageBox::Cancel)//回到编辑状态，等待用户的操作
        ui->pushButton_3->show();
        ui->pushButton_2->show();
        ui->pushButton_4->hide();
        ui->pushButton->hide();
        ui->lineEdit_0->setFocus();

}

void SlamConfig::on_del_clicked()
{
    QSqlQuery query;

    int curRow = ui->tableView->currentIndex().row();     //鼠标选择删除第几行

    QModelIndex index = ui->tableView->currentIndex();

    int id=index.sibling(curRow,0).data().toInt();
    //QString aa = index.sibling(curRow,0).data().toString();
    //QMessageBox::about(this,"About",aa);

    query.prepare("delete from slaminfo where slamid = :id");

    query.bindValue(":id",id);
    query.exec();
    select();
}

void SlamConfig::select()
{
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery(QString("select * from slaminfo"));
    ui->tableView->setModel(model);
}

void SlamConfig::on_search_clicked()
{
          QSqlQuery query;
          ui ->tableView -> clearSpans(); //tableview清空
          QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
          query.prepare("select  * from slaminfo where slamname = :name ");  //like模糊查询没成功
          query.bindValue(":name",ui->lineEdit_11->text());
          query.exec();
          model->setQuery(query);
          ui->tableView->setModel(model);
}

void SlamConfig::on_back_clicked()
{
    select();
    /*QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery(QString("select * from slaminfo"));
    ui->tableView->setModel(model);
    */

}
