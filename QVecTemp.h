/**
*	@file QVecTemp.h
*	@brief file contains the definaion of the class QVecTemp
*	@author Mikayel Egibyan
*/


#ifndef QVECTEMP_H
#define QVECTEMP_H

#include <QVector>
#include <QPointF>
#include <QtMath>

template <class T>
class QVecTemp
{
public:
    static QVector<QVector<T> > SplitVector(QVector<T> items, int clustNum)
    {
        QVector< QVector<T> > allGroups;
        //split the list into equal groups
        int startIndex = 0;
        int groupLength = (int)qRound((float)items.count() / (float)clustNum);
        while (startIndex < items.count())
        {
            QVector<T> group;
            //QVector<T> QVector::mid(int pos, int length = -1);
            for(int i= startIndex; i<groupLength; i++)
            {
                group.append(items.at(i));
            }
            startIndex += groupLength;

            //adjust group-length for last group
            if (startIndex + groupLength > items.count())
            {
                groupLength = items.count() - startIndex;
            }

            allGroups.push_back(group);
        }

        //merge last two groups, if more than required groups are formed
        if (allGroups.count() > clustNum && allGroups.count() > 2)
        {
            int num = allGroups.count() -2;
            allGroups.insert(num, allGroups.last());
            allGroups.remove(allGroups.count() - 1);
        }
        return (allGroups);
    }
private:
};

#endif // QVECTEMP_H
