#include "workwithdatabase.h"
#include "ui_workwithdatabase.h"
#include "addinfo.h" // Добавлено для использования AddInfo
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord> // Добавлено для использования QSqlRecord
#include <QDebug>
#include <QMessageBox>
#include <QString>

WorkWithDatabase::WorkWithDatabase(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WorkWithDatabase)
{
    ui->setupUi(this);
    this->resize(800, 600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(50, 130, 200));
    this->setPalette(palette);
}

WorkWithDatabase::~WorkWithDatabase()
{
    delete ui;
}

void WorkWithDatabase::updateUI(bool type1Visible, bool type2Visible)
{
    ui->textEdit_4->setVisible(type1Visible);
    ui->label_4->setVisible(type1Visible);
    ui->textEdit_2->setVisible(true);
    ui->textEdit_3->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
}

void WorkWithDatabase::on_radioButton_clicked()
{
    updateUI(true, false);
}

void WorkWithDatabase::on_radioButton_2_clicked()
{
    updateUI(false, true);
}

void WorkWithDatabase::handleDatabaseError(const QSqlError &error, const QString &message)
{
    QMessageBox::critical(this, message, error.text());
}

void WorkWithDatabase::executeQuery(const QString &queryStr, QString &result)
{
    QSqlQuery qry;
    if (!qry.exec(queryStr)) {
        ui->textEdit->setText("Error with query");
        return;
    }

    while (qry.next()) {
        QSqlRecord record = qry.record(); // Получение записи
        for (int i = 0; i < record.count(); ++i) { // Использование записи для получения значений
            result += qry.value(i).toString() + " ";
        }
        result += "\n";
    }
    result += "------------------------------------------------------------------------------------\n";
}

void WorkWithDatabase::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if (!db.open()) {
        handleDatabaseError(db.lastError(), "Database error: Trouble with your database");
        return;
    }

    QString final;
    executeQuery("SELECT * FROM Flower", final);
    executeQuery("SELECT * FROM Composition", final);
    executeQuery("SELECT * FROM User", final);

    ui->textEdit->setText(final);
}

void WorkWithDatabase::refreshData()
{
    on_pushButton_2_clicked();
}

bool WorkWithDatabase::isType1Selected() const
{
    return ui->radioButton->isChecked();
}

bool WorkWithDatabase::isType2Selected() const
{
    return ui->radioButton_2->isChecked();
}

void WorkWithDatabase::on_pushButton_clicked()
{
    connect(win1, &AddInfo::databaseUpdated, this, &WorkWithDatabase::refreshData);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if (!db.open()) {
        ui->textEdit->setText("Error: " + db.lastError().text());
        return;
    }

    QString name = ui->textEdit_2->toPlainText();
    QString cost = ui->textEdit_3->toPlainText();
    QString type = ui->textEdit_4->toPlainText();
    QString id;

    QSqlQuery qry;
    if (isType1Selected()) {
        qry.prepare("SELECT COUNT(*) FROM Flower WHERE Name = :name AND Type = :type");
        qry.bindValue(":name", name);
        qry.bindValue(":type", type);
    } else if (isType2Selected()) {
        qry.prepare("SELECT COUNT(*) FROM Composition WHERE Name = :name");
        qry.bindValue(":name", name);
    }

    if (!qry.exec() || !qry.next() || qry.value(0).toInt() > 0) {
        QMessageBox::critical(this, "Slot error", "There is already such slot");
        return;
    }

    if (isType1Selected()) {
        qry.prepare("SELECT MAX(id) FROM Flower");
    } else if (isType2Selected()) {
        qry.prepare("SELECT MAX(id) FROM Composition");
    }

    if (!qry.exec() || !qry.next()) {
        handleDatabaseError(qry.lastError(), "Database error");
        return;
    }

    id = QString::number(qry.value(0).toInt() + 1);

    if (isType1Selected()) {
        qry.prepare("INSERT INTO Flower (id, Name, Type, Cost) VALUES (:id, :name, :type, :cost)");
        qry.bindValue(":type", type);
    } else if (isType2Selected()) {
        qry.prepare("INSERT INTO Composition (id, Name, Cost) VALUES (:id, :name, :cost)");
    }

    qry.bindValue(":id", id);
    qry.bindValue(":name", name);
    qry.bindValue(":cost", cost);

    if (!qry.exec()) {
        handleDatabaseError(qry.lastError(), "Database error");
    } else {
        qDebug() << "Success";
        db.commit();
        db.close();
        refreshData();
    }
}

void WorkWithDatabase::on_pushButton_3_clicked()
{
    win1 = new AddInfo(this);
    win1->show();
}
