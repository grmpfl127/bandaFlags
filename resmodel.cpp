#include "resmodel.h"
#include <QDebug>

resModel::resModel(QList<bandaFlags::ctry> countryL, QList<int> perm, QString picPath, QStringList sub, QStringList ans, QList<bool> hints, QObject *parent) :
    QStandardItemModel(parent)
{
    QList<QStandardItem*> subPtr;
    QList<QStandardItem*> ansPtr;
    QList<QStandardItem*> picPtr;

    for(int i=0; i<sub.size(); i++){
        QStandardItem* subPtrItem = new QStandardItem(sub.at(i));
        QStandardItem* ansPtrItem = new QStandardItem(ans.at(i));
        subPtrItem->setForeground(QBrush(Qt::black));
        ansPtrItem->setForeground(QBrush(Qt::black));
        subPtrItem->setFlags(Qt::NoItemFlags);



        QStandardItem* picPtrItem = new QStandardItem();
        picPtrItem->setData(QVariant(QPixmap(picPath + countryL.at(perm.at(i)).fileName).scaled(QSize(100,100),Qt::KeepAspectRatio,Qt::SmoothTransformation)),Qt::DecorationRole);
        //picPtrItem->setFlags(Qt::ItemIsSelectable);

        if(QString::compare(sub.at(i), ans.at(i),Qt::CaseInsensitive)){
            subPtrItem->setBackground(QBrush(Qt::red));
            ansPtrItem->setBackground(QBrush(Qt::red));
        }else{
            if(hints.at(i)){
                subPtrItem->setBackground(QBrush(Qt::yellow));
                ansPtrItem->setBackground(QBrush(Qt::yellow));
            }else{
                subPtrItem->setBackground(QBrush(Qt::green));
                ansPtrItem->setBackground(QBrush(Qt::green));
            }
        }

        subPtr.append(subPtrItem);
        ansPtr.append(ansPtrItem);
        picPtr.append(picPtrItem);
    }

    insertColumn(0, picPtr);
    insertColumn(1, subPtr);
    insertColumn(2, ansPtr);

    setHorizontalHeaderLabels(QStringList() << "Flags" << "Countries" << "Your Answers");

    subPtr.erase(subPtr.begin(),subPtr.end());
    ansPtr.erase(ansPtr.begin(),ansPtr.end());
    //picPtr.erase(picPtr.begin(),picPtr.end());

    subPtr.clear();
    ansPtr.clear();
    //picPtr.clear();
}


