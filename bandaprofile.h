#ifndef BANDAPROFILE_H
#define BANDAPROFILE_H

#include <QString>
#include <QList>

/*!
 * \brief The bandaProfile class stores the IDs of the already asked flags, the correct answered flags
 * and the not yet guessed flags
 *
 * \param notGuessedIdx;     //IDX of countries of categories
 * \param correctGuessedIdx; //IDX of correctly guessed countries of cats
 * \param alreadyAskedIdx;   //IDX of already asked countries of cats
 */
class bandaProfile
{
public:
    bandaProfile(QString mName);

//private:
    QString name;
    QList<QList <int> > notGuessedIdx;     //IDX of countries of categories
    QList<QList <int> > correctGuessedIdx; //IDX of correctly guessed countries of cats
    QList<QList <int> > alreadyAskedIdx;   //IDX of already asked countries of cats

    QList<int> toggleMemorySize;
};

#endif // BANDAPROFILE_H
