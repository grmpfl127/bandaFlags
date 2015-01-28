#ifndef BANDAPROFILESTATUSDIALOG_H
#define BANDAPROFILESTATUSDIALOG_H

#include <QDialog>
#include <bandaConst.h>
#include <bandaprofile.h>

#include <QVBoxLayout>

namespace Ui {
class bandaProfileStatusDialog;
}

class bandaProfileStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bandaProfileStatusDialog(QString profileName, bandaProfile* bProf, QWidget *parent = 0);
    ~bandaProfileStatusDialog();

private slots:
    void on_okBut_clicked();

private:
    Ui::bandaProfileStatusDialog *ui;
};

#endif // BANDAPROFILESTATUSDIALOG_H
