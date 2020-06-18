#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir dir = QDir::current();
    dir.cdUp();
    QSettings sett(dir.path() + "/settings.ini", QSettings::IniFormat);
    port = sett.value("Firebird/port").toInt();
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
    setWindowTitle("Main page");
    model = new QSqlTableModel(this,db);
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlQueryModel(this);
    model->setQuery("select * from workers");
}
