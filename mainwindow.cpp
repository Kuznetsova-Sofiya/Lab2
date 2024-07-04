#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workwithdatabase.h"
#include "registrationform.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , workingwindow(nullptr)
    , registrationdialog(nullptr)
{
    ui->setupUi(this);
    this->resize(800, 600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(5, 100, 100));
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleDatabaseError(const QSqlError &error, const QString &message)
{
    QMessageBox::warning(this, message, "Troubles with your database: " + error.text());
}

bool MainWindow::executeLoginQuery(const QString &login, const QString &password)
{
    QSqlQuery qry;
    qry.prepare("SELECT COUNT(*) FROM User WHERE login = :login AND password = :password");
    qry.bindValue(":login", login);
    qry.bindValue(":password", password);

    if (!qry.exec()) {
        handleDatabaseError(qry.lastError(), "Database error");
        return false;
    }

    if (qry.next()) {
        return qry.value(0).toInt() > 0;
    }
    return false;
}

void MainWindow::on_LoginButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");

    if (!db.open()) {
        handleDatabaseError(db.lastError(), "Database error");
        return;
    }

    QString login = ui->LoginLine->text();
    QString password = ui->passwordLine->text();

    if (executeLoginQuery(login, password)) {
        hide();
        workingwindow = new WorkWithDatabase(this);
        workingwindow->show();
    } else {
        QMessageBox::warning(this, "Login", "Login or password is incorrect");
    }

    db.close();
}

void MainWindow::on_pushButton_clicked()
{
    registrationdialog = new registrationform(this);
    registrationdialog->show();
}
