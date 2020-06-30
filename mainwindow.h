#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QApplication>
#include <QtSql>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSettings>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    int port;
    QString pass;
    QString hostName;
    QString dbName;
    QString driverName;
    QString userName;
    QString conName;
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
