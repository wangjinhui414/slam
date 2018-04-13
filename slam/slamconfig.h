#ifndef SLAMCONFIG_H
#define SLAMCONFIG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtSql>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <QtDebug>
#include <QCloseEvent>
#include <QObject>

namespace Ui {
class SlamConfig;
}

class SlamConfig : public QDialog
{
    Q_OBJECT

public:
    explicit SlamConfig(QWidget *parent = 0);
    ~SlamConfig();

private slots:

  void on_save_clicked();
  void on_new_clicked();
  void on_cancel_clicked();
  void on_del_clicked();
  void select();
  void on_search_clicked();
  void on_back_clicked();

private:
    Ui::SlamConfig *ui;
};

#endif // SLAMCONFIG_H
