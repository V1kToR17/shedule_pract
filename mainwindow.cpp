#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Main page");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QDir dir = QDir::current();
    dir.cdUp();
    QSettings sett(dir.path() + "/settings.ini", QSettings::IniFormat);
    port = sett.value("PostgreSQL/port").toInt();
    driverName = sett.value("PostgreSQL/driver").toString();
    hostName = sett.value("PostgreSQL/hostname").toString();
    dbName = sett.value("PostgreSQL/dbname").toString();
    userName = sett.value("PostgreSQL/username").toString();
    pass = sett.value("PostgreSQL/password").toString();

    db = QSqlDatabase::addDatabase(driverName);
    db.setPort(port);
    db.setHostName(hostName);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(pass);

    if(!db.open()){
        QMessageBox::critical(nullptr,"Ошибка", "Ошибка подключения к базе данных");
        return;
    }
    model = new QSqlTableModel(this,db);
    ui->tableView->setModel(model);
    QSqlQueryModel(this);
    model->setQuery("select * from workers");
}

void MainWindow::on_pushButton_2_clicked()
{
    QDir dir = QDir::current();
    dir.cdUp();
    QSettings sett(dir.path() + "/settings.ini", QSettings::IniFormat);
    driverName = sett.value("SQLite/driver").toString();
    dbName = sett.value("SQLite/dbname").toString();;

    db = QSqlDatabase::addDatabase(driverName);
    db.setDatabaseName(dbName);

    if(!db.open()){
        QMessageBox::critical(nullptr,"Ошибка", "Ошибка подключения к базе данных");
        return;
    }

    model = new QSqlTableModel(this,db);
    ui->tableView->setModel(model);
    QSqlQueryModel(this);
    model->setQuery("select * from workers");
}

void MainWindow::on_pushButton_3_clicked()
{
//в разработке
    if(db.open()){
        db.close();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
}
