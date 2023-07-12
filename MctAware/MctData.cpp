#include "MctData.h"

MctData::MctData()
{

}

// sets the ip address
void MctData::setIpAddress(const QString ip)
{
    ipAddress = ip.toStdString(); // Changes the QString to a standard Library String
    std::cout << ipAddress << "\n"; // print out the sting for testing

}

//stores the path to the routerCSV
void MctData::setRouterCSV(const QString Router)
{
    routerCSV = Router.toStdString();// Changes the QString to a standard Library String
    std::cout << routerCSV<< "\n";
}

void MctData::setNetwork(const QString NetworkInterface)
{
    networkInterface = NetworkInterface.toStdString(); // Changes the QString to a standard Library String
}
void MctData::setDataCSV(const QString DataCSV)
{
    dataCSV = DataCSV.toStdString();// Changes the QString to a standard Library String
    std::cout << dataCSV<< "\n";
}

std::string MctData::getRouterCSV()
{
    return routerCSV;
}


std::string MctData::getNetwork()
{
    return networkInterface;
}
std::string MctData::getDataCSV()
{
    return dataCSV;
}

std::string MctData::getIpAddress()
{
    return ipAddress;
}

MctData::~MctData()
{

}


