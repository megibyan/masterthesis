#ifndef QVECTEMP_H
#define QVECTEMP_H

#include <QVector>
#include <QPointF>
#include <QtMath>

template <class T>
class QVecTemp
{
public:
    static QVector<QVector<T> > SplitVector(QVector<T>, int);
private:
};

#endif // QVECTEMP_H
