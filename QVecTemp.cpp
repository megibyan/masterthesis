#include "QVecTemp.h"

template <class T>
QVector<QVector<T> > QVecTemp<T>::SplitVector(QVector<T> items, int clustNum)
{
    QVector< QVector<T> > allGroups = new QVector<QVector<T> >();

    //split the list into equal groups
    int startIndex = 0;
    int groupLength = (int)qRound((float)items.count() / (float)clustNum);
    while (startIndex < items.count())
    {
        QVector<T> group = new QVector<T>();
        group.AddRange(items.GetRange(startIndex, groupLength));
        startIndex += groupLength;

        //adjust group-length for last group
        if (startIndex + groupLength > items.count())
        {
            groupLength = items.Count - startIndex;
        }

        allGroups.Add(group);
    }

    //merge last two groups, if more than required groups are formed
    if (allGroups.count() > clustNum && allGroups.count() > 2)
    {
        allGroups[allGroups.count() - 2].append(allGroups.last());
        allGroups.remove(allGroups.count() - 1);
    }

    return (allGroups);
}
