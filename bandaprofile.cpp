#include "bandaprofile.h"
#include "bandaConst.h"

bandaProfile::bandaProfile(QString mName) : name(mName)
{
    QListIterator<int> iter(bandaConst::catSpinMax);
    while(iter.hasNext()){
        notGuessedIdx.append(QList<int>());
        alreadyAskedIdx.append(QList<int>());
        correctGuessedIdx.append(QList<int>());
        toggleMemorySize.append(0);
        iter.next();
    }

}
