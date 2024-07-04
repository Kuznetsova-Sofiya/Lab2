#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QDialog>
#include <QSqlError> // Добавлено для использования QSqlError

namespace Ui {
class registrationform;
}

class registrationform : public QDialog
{
    Q_OBJECT

public:
    explicit registrationform(QWidget *parent = nullptr);
    ~registrationform();

private slots:
    void on_pushButton_clicked();

private:
    Ui::registrationform *ui;
    void handleDatabaseError(const QSqlError &error, const QString &message); // Объявление метода
};

#endif // REGISTRATIONFORM_H
