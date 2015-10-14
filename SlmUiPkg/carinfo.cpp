#include "carinfo.h"
QVector<CarInfo*> CarInfo::v_carInfos = QVector<CarInfo*>(20,0);
CarInfo::CarInfo(const QString& _carID)
{
    this->carID = _carID;
}
