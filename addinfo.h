#ifndef ADDINFO_H
#define ADDINFO_H

#include <QDialog>

namespace Ui {
class AddInfo;
}

class AddInfo : public QDialog
{
    Q_OBJECT

public:
    explicit AddInfo(QWidget *parent = nullptr);
    ~AddInfo();

private slots:
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateUI();

signals:
    void databaseUpdated();

private:
    Ui::AddInfo *ui;
};

#endif // ADDINFO_H
