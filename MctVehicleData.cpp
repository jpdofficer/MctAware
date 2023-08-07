#include "MctVehicleData.h"

MctVehicleData::MctVehicleData()
{
    autoTimeStamp();
    setRouterIP("192.168.0.1");

    //initalize the Map
    MctVehicleDataMap = std::map<std::string, std::string>();
    myNet = std::make_unique<NetworkInformation>();
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
    setRouterMac(myNet->arpMacAddress(this->getRouterIP()));
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
    QString routerMacString = QString::fromStdString(routerMac);
    if(routerMacString.startsWith("2A"))
    {
            routerMacString.replace(0,2, "00");
       MctVehicleDataMap["router_mac"] = routerMacString.toStdString();
    }
    else
    {
        MctVehicleDataMap["router_mac"] = routerMac;
    }
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


std::string MctVehicleData::getTimeStamp()
{
     return MctVehicleDataMap["timeStamp"];
}

std::string MctVehicleData::getUserName()
{
     return MctVehicleDataMap["user_name"];
}
std::string MctVehicleData::getComputerName()
{
     return MctVehicleDataMap["computer_name"];
}
std::string MctVehicleData::getComputerMacAddress()
{
     return MctVehicleDataMap["computer_mac"];
}

std::string MctVehicleData::getRouterName()
{
     return MctVehicleDataMap["router_name"];
}
std::string MctVehicleData::getRouterMac()
{
    return  MctVehicleDataMap["router_mac"];
}

std::string MctVehicleData::getRouterSerial()
{
    return MctVehicleDataMap["router_serial"];
}
std::string MctVehicleData::getRouterState()
{
    return MctVehicleDataMap["router_state"];
}
std::string MctVehicleData::getRouterCSVPath()
{
    return MctVehicleDataMap["router_cvs_path"];
}
std::string MctVehicleData::getMCTVehicleCSVPath()
{
   return MctVehicleDataMap["association_cvs_path"];
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


void MctVehicleData::writeConfig(QFile &file)
{
     QXmlStreamWriter xmlWriter(&file);
     xmlWriter.setAutoFormatting(true); // make it human readable

     //Write the XML start document
     xmlWriter.writeStartDocument();

     //Write the root element
     xmlWriter.writeStartElement("Config");

     //write the routers ip address
     xmlWriter.writeStartElement("ip");
     xmlWriter.writeCharacters(QString::fromStdString(getRouterIP()));
     xmlWriter.writeEndElement();

     //write the routers mac address
     xmlWriter.writeStartElement("router_mac");
     xmlWriter.writeCharacters(QString::fromStdString(getRouterMac()));
     xmlWriter.writeEndElement();

     //write the router cvs location
     xmlWriter.writeStartElement("routerCvs");
     xmlWriter.writeCharacters(QString::fromStdString(getRouterCSVPath()));
     xmlWriter.writeEndElement();

     //Write network interface
     xmlWriter.writeStartElement("interface");
     xmlWriter.writeCharacters(QString::fromStdString(getInterface()));
     xmlWriter.writeEndElement();

     //Write vehicle CSV Location
     xmlWriter.writeStartElement("vehicleCvs");
     xmlWriter.writeCharacters(QString::fromStdString(getMCTVehicleCSVPath()));
     xmlWriter.writeEndElement();

     //Write the root elements end
     xmlWriter.writeEndElement();

     //Write the XML document's end
     xmlWriter.writeEndDocument();

     //close the file
     file.close();
}

void MctVehicleData::writeConfigXMLFile()
{
#ifdef Q_OS_WIN

     QString configDir ="C:\TEMP\COMPDIR\MCTAware"; //The directory that store the config file

     QDir directoryWin(configDir)
         if(!directory.exists())  //check if the directory exist
     {
            directory.mkpath(configDir); // if it does not exist we create it
     }
     else
     {
            QMessageBox::critical(this, "Error", "Unable create config file!"); // if we cannot create it we give a error
     }

            QString WindowsFilePath = "C:\TEMP\COMPDIR\MCTAware\.config.xml";

            QFile file(WindowsFilePath);
            if(!file.exists())
            {
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::critical(nullptr, "Error", "Unable create config file!");
            }
            writeConfig(&file);




     }
     }
#elif defined(Q_OS_LINUX)

     QString configDirLinux = "/home/jyeager/Temp/MctAware/";
     QDir directory(configDirLinux);
     if(!directory.exists()) //check if the directory exist
     {
            directory.mkpath(configDirLinux); // if it does not exist we create it
     }


            QString linuxFilePath = "/home/jyeager/Temp/MctAware/.config.xml";
            QFile file(linuxFilePath);
            if(!file.exists())
            {
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::critical(nullptr, "Error", "Unable create config file!");
            }
            writeConfig(file);


     }
#endif

}
