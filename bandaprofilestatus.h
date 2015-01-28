#ifndef BANDAPROFILESTATUS_H
#define BANDAPROFILESTATUS_H

#include <QWidget>
#include <bandaConst.h>
#include <bandaprofile.h>


namespace Ui {
class bandaProfileStatus;
}

class bandaProfileStatus : public QWidget
{
    Q_OBJECT

public:
    explicit bandaProfileStatus(QString profileName, bandaProfile* bProf, QWidget *parent = 0);
    ~bandaProfileStatus();

private:
    Ui::bandaProfileStatus *ui;
};

#endif // BANDAPROFILESTATUS_H
