#ifndef CRADLEPOINTROUTER_H
#define CRADLEPOINTROUTER_H
#include<QFile>
#include<QTextStream>
#include<QStringList>
#include<QMap>
#include<memory>

#include<iostream>
#include "router.h"
#include "MctVehicleData.h"

class CradlePointRouter : public Router
{
public:
    CradlePointRouter();
    void setRouterFile(QString & file);

private:
    QMap<QString,QString>cradlePointCSV;
    std::unique_ptr<MctVehicleData>VehicleData;
};

#endif // CRADLEPOINTROUTER_H
