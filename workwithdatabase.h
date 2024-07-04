#ifndef WORKWITHDATABASE_H
#define WORKWITHDATABASE_H

#include <QDialog>
#include <QSqlError> // Добавлено для использования QSqlError

class AddInfo; // Добавлено для объявления класса AddInfo

namespace Ui {
class WorkWithDatabase;
}

class WorkWithDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit WorkWithDatabase(QWidget *parent = nullptr);
    ~WorkWithDatabase();

private slots:
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void refreshData();

private:
    Ui::WorkWithDatabase *ui;
    void updateUI(bool type1Visible, bool type2Visible);
    void executeQuery(const QString &queryStr, QString &result);
    void handleDatabaseError(const QSqlError &error, const QString &message);
    bool isType1Selected() const;
    bool isType2Selected() const;

    AddInfo *win1;
};

#endif // WORKWITHDATABASE_H
