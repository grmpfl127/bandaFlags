#include "result.h"
#include "resmodel.h"

#include <QHeaderView>

myResult::myResult(QList<bandaFlags::ctry> countryL, QList<int> perm, QString picPath, QStringList subset, QStringList answers, QList<bool> hintsUsed, int right, int total, QWidget *parent) :
    QDialog(parent)
{
    resView = new QTableView(this);
    mModel = new resModel(countryL, perm, picPath, subset, answers, hintsUsed, this);

    resView->setModel(mModel);
    //resView->resize(QSize(parent->width()));
    QFont bandaFont = QFont("Georgia",-1,QFont::Bold,false);
    QHeaderView* vertHeader = resView->verticalHeader();
    vertHeader->setDefaultSectionSize(50);

    resView->setVerticalHeader(vertHeader);
    resView->setFont(bandaFont);
    resView->horizontalHeader()->setFont(bandaFont);
    resView->resizeColumnsToContents();


    okBut = new QPushButton(tr("Ok"),this);
    label = new QLabel(QString("%1 out of %2 answers correct").arg(right).arg(total));
    label->setFont(QFont("Georgia",18,QFont::Bold,false));
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* vLay = new QVBoxLayout(this);
    vLay->addWidget(label);
    vLay->addWidget(resView);
    vLay->addWidget(okBut);
    setLayout(vLay);
    setWindowTitle("Results");

    connect(okBut,SIGNAL(clicked()),this,SLOT(accept()));
}
