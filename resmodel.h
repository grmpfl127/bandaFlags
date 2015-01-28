#ifndef RESMODEL_H
#define RESMODEL_H

#include <QStandardItemModel>
#include "bandaflags.h"

class resModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit resModel(QList<bandaFlags::ctry> countryL, QList<int> perm, QString picPath, QStringList sub, QStringList ans, QList<bool> hints, QObject *parent = 0);
signals:

public slots:

private:
    void style();
};

#endif // RESMODEL_H
