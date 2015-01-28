#ifndef BANDAPROFILEVIEW_H
#define BANDAPROFILEVIEW_H

#include "bandaflags.h"

#include <QListView>
#include <QKeyEvent>
#include <QMessageBox>

class bandaProfileView : public QListView
{
    Q_OBJECT
public:
    explicit bandaProfileView(QWidget *parent = 0);
    //reimplement enter event
    void keyPressEvent(QKeyEvent* e);

signals:
    void ready();

public slots:



};

#endif // BANDAPROFILEVIEW_H
