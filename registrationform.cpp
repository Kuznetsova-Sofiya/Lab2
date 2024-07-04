#include "registrationform.h"
#include "ui_registrationform.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>

registrationform::registrationform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registrationform)
{
    ui->setupUi(this);
    this->resize(800, 600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(113, 85, 92));
    this->setPalette(palette);
}

registrationform::~registrationform()
{
    delete ui;
}

void registrationform::handleDatabaseError(const QSqlError &error, const QString &message) {
    QMessageBox::critical(this, message, error.text());
}

void registrationform::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if (!db.open()) {
        handleDatabaseError(db.lastError(), "Database error: Trouble with your database");
        return;
    }

    QString newlogin = ui->lineEdit->text();
    QString newpassword = ui->lineEdit_2->text();

    QSqlQuery qry;

    if (!qry.exec("SELECT MAX(id) FROM User")) {
        handleDatabaseError(qry.lastError(), "Database error");
        return;
    }

    QString newid = "1"; // Default id if no previous id is found
    if (qry.next()) {
        newid = QString::number(qry.value(0).toInt() + 1);
    }

    qry.prepare("SELECT COUNT(*) FROM User WHERE login = :login");
    qry.bindValue(":login", newlogin);
    if (!qry.exec() || !qry.next()) {
        handleDatabaseError(qry.lastError(), "Database error");
        return;
    }

    int count = qry.value(0).toInt();
    if (count > 0) {
        QMessageBox::warning(this, "Login", "User with such login has already registered");
    } else {
        qry.prepare("INSERT INTO User (id, Login, Password) VALUES(:id, :login, :password)");
        qry.bindValue(":id", newid);
        qry.bindValue(":login", newlogin);
        qry.bindValue(":password", newpassword);

        if (!qry.exec()) {
            handleDatabaseError(qry.lastError(), "Database error");
            return;
        }

        QMessageBox::information(this, "Registration", "Registration successful");
        db.close();
        hide();
    }
}
