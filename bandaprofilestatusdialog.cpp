#include "bandaprofilestatusdialog.h"
#include "ui_bandaprofilestatusdialog.h"

#include <QDebug>

bandaProfileStatusDialog::bandaProfileStatusDialog(QString profileName, bandaProfile* bProf, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bandaProfileStatusDialog)
{
    ui->setupUi(this);

    //set up categories
    QList<QLabel*> allLabels = findChildren<QLabel*>();
    QListIterator<QLabel*> labelIter(allLabels);
    QRegExp rxLabel("^catLabel_(.*)$");
    QRegExp rxTotal("^catTotal_(.*)$");

    while(labelIter.hasNext()){
        QLabel* next = labelIter.next();

        if(next->objectName().contains(rxLabel)){
            next->setText(QString("%1").arg(bandaConst::catList.at(rxLabel.cap(1).toInt()-1)));
        }
        else if(next->objectName().contains("profileNameLabel")){
            next->setText(profileName);
        }
        else if(next->objectName().contains(rxTotal)){
            next->setAlignment(Qt::AlignRight);
            QString correct = QString::number(bProf->correctGuessedIdx.at(rxTotal.cap(1).toInt()-1).size());
            QString total = QString::number(bandaConst::catSpinMax.at(rxTotal.cap(1).toInt()-1));
            next->setText(QString("%1 out of %2 correct").arg(correct,total));
            if(correct.toInt() == total.toInt()){
                next->setStyleSheet("color: green");
            }
        }
    }


    //set up stats
    QList<QProgressBar*> allProgress = findChildren<QProgressBar*>();
    QListIterator<QProgressBar*> progressIter(allProgress);
    QRegExp rxProg("^catProgress_(.*)$");
    int cnt = 0;
    while(progressIter.hasNext()){
        QProgressBar* nextProg = progressIter.next();
        if(nextProg->objectName().contains(rxProg)){
            nextProg->setTextVisible(true);
            nextProg->setStyleSheet("");
            int percentage = (static_cast<double>(bProf->correctGuessedIdx.at(rxProg.cap(1).toInt()-1).size())/static_cast<double>(bandaConst::catSpinMax.at(rxProg.cap(1).toInt()-1)))*100;
            nextProg->setValue(percentage);
            nextProg->setTextVisible(false);
            cnt++;
        }
    }

    setWindowTitle(tr("Profile Summary"));

}

bandaProfileStatusDialog::~bandaProfileStatusDialog()
{
    delete ui;
}

void bandaProfileStatusDialog::on_okBut_clicked()
{
    this->accept();
}
