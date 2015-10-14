#ifndef CARINFO_H
#define CARINFO_H
#include<QString>
#include<QVector>
class CarInfo
{
public:
    CarInfo(const QString& carName);
    QString carID;
    QString slm1;
    QString slm2;
    static QVector<CarInfo*> v_carInfos;
};

#endif // CARINFO_H
