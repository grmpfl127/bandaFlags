#include "bandaprofileview.h"

#include <QDebug>

bandaProfileView::bandaProfileView(QWidget *parent) :
    QListView(parent)
{
    emit ready();


    QString stylesheet = "";
    stylesheet += QString("bandaProfileView::item:selected {background-color: %1 ;}").arg(bandaConst::bandaColor);
    stylesheet += QString("bandaProfileView::item:hover {background-color: %1 ;}").arg(bandaConst::bandaColorMarked);
    setStyleSheet(stylesheet);
}

void bandaProfileView::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Delete){
        //this->model()->removeRow(currentIndex().row());
        //this->parent()->parent()->;
    }else{
        QListView::keyPressEvent(e);
    }
}
