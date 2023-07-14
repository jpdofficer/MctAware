#include "MctVehicleData.h"

MctVehicleData::MctVehicleData(std::string ip)
{

    setRouterIP(ip);
}


/*Create a timestamp */
void MctVehicleData::autoTimeStamp()
{
    //get the current time
    auto currentTime = std::chrono::system_clock::now();

    //Convert the system time to a time_t value
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);

    //convert to a string
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%A %c",std::localtime(&time));
    MctVehicleDataMap["timeStamp"] = buffer;
}

void MctVehicleData::autoUserName() {}


void MctVehicleData::autoComputerIP()
{
  //Get the ip address from the selected network interface
    QNetworkInterface networkInterface = QNetworkInterface::interfaceFromName(QString::fromStdString(data.getNetwork()));
    if (networkInterface.isValid()) { // if the networkInterface is valid
        QList<QNetworkAddressEntry> addressEntries = networkInterface.addressEntries(); // get the networkInterfacee address entries and add it to a QList
        for (const QNetworkAddressEntry& entry : addressEntries) {   // go through the list
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {  //make sure that the ip protocol is ipv4
                 MctVehicleDataMap["computer_ip"] = entry.ip().toString().toStdString(); // assign the ip to the MctVehicleDataMap
                return; // Stop after finding the first IPv4 address
            }
        }
    }
    // Handle the case when the network interface is not found or has no IPv4 address

}
void MctVehicleData::autoRouterIP(std::string routerIP) {}
void MctVehicleData::autoRouterMac() {}


void MctVehicleData::autoComputerMacAddress()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces(); // get the all interfaces and place it in interfaces
    for( const QNetworkInterface & interface : interfaces) // loop through the interfaces
    {
        if(interface.isValid() && !interface.hardwareAddress().isEmpty()) // if the interface is valid and the hardwareaddress of that address is not empty
        {
            MctVehicleDataMap["computer_mac"] = interface.hardwareAddress().toStdString(); //assign it to the datamap
        }
    }
}


void MctVehicleData::autoComputerName()
{
    MctVehicleDataMap["computer_name"] = QSysInfo::machineHostName().toStdString(); //get the machine host name and assign it to the datamap
}

/* Set Functions */
void MctVehicleData::setUserName(std::string uname)
{
    //set the Datamap key user_name
    MctVehicleDataMap["user_name"] = uname;
}
void MctVehicleData::setComputerName(std::string compName)
{
    MctVehicleDataMap["computer_name"] = compName;
}
void MctVehicleData::setComputerMacAddress(std::string computerMac)
{
    MctVehicleDataMap["computer_mac"] = computerMac;
}
void MctVehicleData::setComputerIP(std::string computerIP)
{
    MctVehicleDataMap["computer_ip"] = computerIP;
}
void MctVehicleData::setRouterName(std::string routerName)
{
    MctVehicleDataMap["router_name"] = routerName;
}
void MctVehicleData::setRouterMac(std::string routerMac)
{
    MctVehicleDataMap["router_mac"] = routerMac;
}
void MctVehicleData::setRouterIP(std::string routerIP)
{
     MctVehicleDataMap["router_ip"] = routerIP;
}
void MctVehicleData::setRouterSerial(std::string routerSerial)
{
     MctVehicleDataMap["router_serial"] = routerSerial;
}
void MctVehicleData::setRouterState(std::string routerState)
{
     MctVehicleDataMap["router_state"] = routerState;
}
void MctVehicleData::setRouterCSVPath(std::string routerCSVPath)
{
     MctVehicleDataMap["router_cvs_path"] = routerCSVPath;
}
void MctVehicleData::setMCTVehicleCSVPath(std::string mctVehiclePath)
{
     MctVehicleDataMap["association_cvs_path"] = mctVehiclePath;
}
void MctVehicleData::setInterface(std::string interface)
{
     MctVehicleDataMap["computer_interface"] = interface;
     std::cout << MctVehicleDataMap["computer_interface"] << "\n";
}


std::string MctVehicleData::getComputerIP()
{
     return MctVehicleDataMap["computer_ip"];
}

std::string MctVehicleData::getRouterIP()
{
     return MctVehicleDataMap["router_ip"];
}




