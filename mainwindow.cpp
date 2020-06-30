#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel(this);
    model = new QSqlTableModel(this,db);
    setWindowTitle("Main page");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}


void MainWindow::on_pushButton_clicked()
{
    QDir dir = QCoreApplication::applicationDirPath();
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

    ui->tableView->setModel(model);
    model->setQuery("select worker_fio, start_work, finish_work from workers");
}

void MainWindow::on_pushButton_2_clicked()
{
    QDir dir = QCoreApplication::applicationDirPath();
    QSettings sett(dir.path() + "/settings.ini", QSettings::IniFormat);
    driverName = sett.value("SQLite/driver").toString();
    dbName = sett.value("SQLite/dbname").toString();;

    db = QSqlDatabase::addDatabase(driverName);
    db.setDatabaseName(dbName);

    if(!db.open()){
        QMessageBox::critical(nullptr,"Ошибка", "Ошибка подключения к базе данных");
        return;
    }

    ui->tableView->setModel(model);
    model->setQuery("select worker_fio, start_work, finish_work from workers");
}

void MainWindow::on_pushButton_3_clicked()
{
    if(db.open()){
        ui->tableView->setModel(0);
        db.close();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString fio = ui->lineEdit->text();
    QString start = ui->lineEdit_2->text();
    QString finish = ui->lineEdit_3->text();
    if (db.open() and fio!="" and start!="" and finish!=""){
        model->setQuery("insert into workers (worker_fio, start_work, finish_work) values ('"+fio+"', '"+start+"', '"+finish+"')");
        model->setQuery("select worker_fio, start_work, finish_work from workers");
    }
    else{
        QMessageBox::critical(nullptr,"Ошибка", "Ошибка ввода данных");
        return;
    }
}
