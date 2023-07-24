#include "MctVehicleData.h"

MctVehicleData::MctVehicleData()
{
    autoTimeStamp();
    setRouterIP("192.168.0.1");

    //initalize the Map
    MctVehicleDataMap = std::map<std::string, std::string>();
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

void MctVehicleData::autoUserName()
{
    if (QOperatingSystemVersion::current() <= QOperatingSystemVersion::Windows10) {
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
            //QFileInfo fileInfo(homePath);
        QDir homeDir(homePath);
        QString userName = homeDir.dirName();
        setUserName(userName.toStdString());


    }
    else
    {

        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QString userName = homePath.section(QDir::separator(), -1);

        setUserName(userName.toStdString());
    }



}




void MctVehicleData::autoComputerIP()
{
  //Get the ip address from the selected network interface
    QNetworkInterface networkInterface = QNetworkInterface::interfaceFromName(QString::fromStdString(getInterface()));
    if (networkInterface.isValid()) { // if the networkInterface is valid
        QList<QNetworkAddressEntry> addressEntries = networkInterface.addressEntries(); // get the networkInterfacee address entries and add it to a QList
        for (const QNetworkAddressEntry& entry : addressEntries) {   // go through the list
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {  //make sure that the ip protocol is ipv4
                setComputerIP( entry.ip().toString().toStdString()); // assign the ip to the MctVehicleDataMap
                return; // Stop after finding the first IPv4 address
            }
        }
    }
    // Handle the case when the network interface is not found or has no IPv4 address
    else
    {
        setComputerIP( "Invalid Computer IP");
    }
}
//void MctVehicleData::autoRouterIP(const std::string routerIP) {}
void MctVehicleData::autoRouterMac() {
    try {
        // Run the 'arp' command to get the MAC address of the router
        QString routerIP = QString::fromStdString(getRouterIP()); // Replace with the appropriate method to get the router IP address
    //    QString arpCommand = "arp -n " + routerIP;
        QProcess arpProcess;
        arpProcess.start("arp", QStringList() << "-n" << routerIP);
        arpProcess.waitForFinished();

        // Read the output of the 'arp' command
        QByteArray arpResult = arpProcess.readAll();
        QString arpOutput = QString::fromLocal8Bit(arpResult);

        // Parse the output to extract the MAC address
        QStringList arpLines = arpOutput.split('\n');
        QString routerMAC;
        for (const QString& line : arpLines) {
            QStringList columns = line.trimmed().split(QRegularExpression("\\s+"));
            if (columns.size() >= 3 && columns[0] == routerIP) {
                routerMAC = columns[2];
                break;
            }
        }

        // Update the router MAC address in your data structure
        MctVehicleDataMap["router_mac"] = routerMAC.toStdString();
    } catch (const std::exception& e) {
        // Exception handling for std::exception or its derived types
        qDebug() << "Exception occurred: " << e.what();
        // Handle the exception appropriately
    } catch (...) {
        // Catch-all for any other exceptions
        qDebug() << "Unknown exception occurred";
        // Handle the exception appropriately
    }
}


void MctVehicleData::autoComputerMacAddress()
{
    QNetworkInterface interfaces = QNetworkInterface::interfaceFromName(QString::fromStdString(getInterface())); // get the all interfaces and place it in interfaces

        if(interfaces.isValid() && !interfaces.hardwareAddress().isEmpty()) // if the interface is valid and the hardwareaddress of that address is not empty
        {
            setComputerMacAddress( interfaces.hardwareAddress().toStdString()) ; //assign it to the datamap
        }

}


void MctVehicleData::autoComputerName()
{
        setComputerName( QSysInfo::machineHostName().toStdString() ); //get the machine host name and assign it to the datamap
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

}


std::string MctVehicleData::getComputerIP()
{
     return MctVehicleDataMap["computer_ip"];
}

std::string MctVehicleData::getRouterIP()
{
     return MctVehicleDataMap["router_ip"];
}


std::string MctVehicleData::getInterface()
{
     return MctVehicleDataMap["computer_interface"];
}



