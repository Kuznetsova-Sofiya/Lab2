#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlError> // Добавлено для использования QSqlError

class WorkWithDatabase; //  для объявления класса WorkWithDatabase
class registrationform; //  для объявления класса registrationform

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoginButton_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    WorkWithDatabase *workingwindow;
    registrationform *registrationdialog;

    void handleDatabaseError(const QSqlError &error, const QString &message);
    bool executeLoginQuery(const QString &login, const QString &password);
};

#endif // MAINWINDOW_H
