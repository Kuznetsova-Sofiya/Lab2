#include "addinfo.h"
#include "ui_addinfo.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "workwithdatabase.h"

bool type_1 = false;
bool type_2 = false;

AddInfo::AddInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddInfo)
{
    ui->setupUi(this);
    this->resize(800, 600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(150, 70, 102));
    this->setPalette(palette);
}

AddInfo::~AddInfo()
{
    delete ui;
}

void AddInfo::on_radioButton_clicked()
{
    type_1 = true;
    type_2 = false;
    updateUI();
}

void AddInfo::on_radioButton_2_clicked()
{
    type_1 = false;
    type_2 = true;
    updateUI();
}

void AddInfo::updateUI()
{
    ui->label_3->setVisible(type_1);
    ui->textEdit_3->setVisible(type_1);
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->textEdit->setVisible(true);
    ui->textEdit_2->setVisible(true);
}

void AddInfo::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        ui->textEdit->setText("Error: " + db.lastError().text());
        return;
    }

    QString id = ui->textEdit_4->toPlainText();
    QString name = ui->textEdit->toPlainText();
    QString cost = ui->textEdit_2->toPlainText();
    QString type = ui->textEdit_3->toPlainText();
    QString queryStr;

    if(type_1){
        queryStr = "UPDATE Flower SET id=:id, Name=:name, Type=:type, Cost=:cost WHERE id=:id";
    } else if(type_2){
        queryStr = "UPDATE Composition SET id=:id, Name=:name, Cost=:cost WHERE id=:id";
    }

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":cost", cost);
    if(type_1) {
        query.bindValue(":type", type);
    }

    if(!query.exec()){
        qDebug() << "Error:" << query.lastError().text();
    } else {
        qDebug() << "Success";
        db.commit();
        db.close();
        emit databaseUpdated();
    }
}

void AddInfo::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        ui->textEdit->setText("Error: " + db.lastError().text());
        return;
    }
    QSqlQuery query;
    QString id = "";
    id = ui->textEdit_4->toPlainText();

    if(type_1){
        query.prepare("DELETE FROM Flower WHERE id=:id");
        query.bindValue(":id", id);
        if(!query.exec()){
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            emit databaseUpdated();
        }
    }
    if(type_2){
        query.prepare("DELETE FROM Composition WHERE id=:id");
        query.bindValue(":id", id);
        if(!query.exec()){
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            emit databaseUpdated();
        }
    }
}

