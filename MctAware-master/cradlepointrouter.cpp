#include "cradlepointrouter.h"

CradlePointRouter::CradlePointRouter()
{
    //creates a cradlepoint router
    VehicleData = std::make_unique<MctVehicleData>();
    //Router::setRouter(cradlePointCSV,QString::fromStdString(VehicleData->getRouterCSVPath()));
}


void CradlePointRouter::setRouterFile(QString & filePath)
{
    Router::setRouter(cradlePointCSV,QString::fromStdString(VehicleData->getRouterCSVPath()));
}
