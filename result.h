#ifndef RESULT_H
#define RESULT_H

#include <QStandardItemModel>
#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include "bandaflags.h"
#include "resmodel.h"
#include "bandaprofilestatusdialog.h"

class myResult : public QDialog
{
    Q_OBJECT
public:
    myResult(QList<bandaFlags::ctry> countryL, QList<int> perm, QString picPath, QStringList subset, QStringList answers, QList<bool> hintsUsed,int right, int total, QWidget *parent=0);
    myResult(QList<bandaFlags::ctry> countryL, QList<int> perm, QString picPath, QStringList subset, int right, int total, QWidget *parent=0);
signals:

public slots:

private:
    QLabel* label;
    QPushButton* okBut;
    QTableView* resView;
    resModel* mModel;
};

#endif // RESULT_H
