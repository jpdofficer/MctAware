#include "MctVehicleData.h"

MctVehicleData::MctVehicleData()
{
    autoTimeStamp();
    setRouterIP("192.168.0.1");

    //initalize the Map
    MctVehicleDataMap = QMap<std::string, std::string>();
    myNet = std::make_unique<NetworkInformation>();
    myModem = std::make_unique<Modem>();
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





//void MctVehicleData::autoRouterIP(const std::string routerIP) {}
void MctVehicleData::autoRouterMac() {
    setRouterMac(myNet->arpMacAddress(this->getRouterIP()));
}


void MctVehicleData::autoComputerMacAddress()
{
    setComputerMacAddress(myNet ->getSelectedIfMac(this->getInterface()));

}


void MctVehicleData::autoComputerName()
{
        //setComputerName( QSysInfo::machineHostName().toStdString() ); //get the machine host name and assign it to the datamap
        setComputerName(myComputer->getMachineName().toStdString());
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

void MctVehicleData::setIMEI()
{
     std::string value = myModem ->getIMEI().toStdString();
     if(!value.empty())
        MctVehicleDataMap["IMEI"] = myModem ->getIMEI().toStdString();
}


void MctVehicleData::setIMSI()
{
     std::string value = myModem ->getIMSI().toStdString();
     if(!value.empty())
        MctVehicleDataMap["IMSI"] = myModem ->getIMSI().toStdString();
}

void MctVehicleData::setNumber()
{
     std::string value = myModem ->getNumber().toStdString();
     if(!value.empty())
        MctVehicleDataMap["Number"] = myModem ->getNumber().toStdString();
}

void MctVehicleData::setICCID()
{
     std::string value = myModem ->getICCID().toStdString();
     if(!value.empty())
        MctVehicleDataMap["ICCID"] = myModem ->getICCID().toStdString();
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

std::string MctVehicleData::getIMEI()
{
     return MctVehicleDataMap["IMEI"];
}

std::string MctVehicleData::getIMSI()
{
     return MctVehicleDataMap["IMSI"];
}

std::string MctVehicleData::getNumber()
{
     return MctVehicleDataMap["Number"];
}

std::string MctVehicleData::getICCID()
{
     return MctVehicleDataMap["ICCID"];
}

void MctVehicleData::writeConfig(QFile &file)
{
     QXmlStreamWriter xmlWriter(&file);
     xmlWriter.setAutoFormatting(true); // make it human readable

     //Write the XML start document
     xmlWriter.writeStartDocument();

     //Write the root element
     xmlWriter.writeStartElement("Config");

     //write the computer ip
     xmlWriter.writeStartElement("computer_ip");
     xmlWriter.writeCharacters(QString::fromStdString(getComputerIP()));
     xmlWriter.writeEndElement();




     //write the routers ip address
     xmlWriter.writeStartElement("router_ip");
     xmlWriter.writeCharacters(QString::fromStdString(getRouterIP()));
     xmlWriter.writeEndElement();


     //write the computer mac address
     xmlWriter.writeStartElement("computer_mac");
     xmlWriter.writeCharacters(QString::fromStdString(getComputerMacAddress()));
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

     if(getIMEI() != "")
     {
        xmlWriter.writeStartElement("IMEI");
        xmlWriter.writeCharacters(QString::fromStdString(getIMEI()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("IMSI");
        xmlWriter.writeCharacters(QString::fromStdString(getIMSI()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("Number");
        xmlWriter.writeCharacters(QString::fromStdString(getNumber()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ICCID");
        xmlWriter.writeCharacters(QString::fromStdString(getICCID()));
        xmlWriter.writeEndElement();
     }

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

int MctVehicleData::createCSV()
{
     QString myFilePath = "/home/jyeager/Temp/MctAware/assignment.csv"; //the file path
     QFile file(myFilePath); //create a pointer to the file path

     if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QTextStream stream(&file);
        //get all the keys and make a header file
        for(auto it = MctVehicleDataMap.constBegin(); it != MctVehicleDataMap.constEnd(); ++it)
        {
            stream << QString::fromStdString(it.key());
            if( it != MctVehicleDataMap.constEnd())
            {
                stream << ",";
            }// end if that inserts a comma after every header

        }//end for loop for headers
        stream << "\n"; //start a new line

        //Write the maps values into the the CSV
        for (auto it = MctVehicleDataMap.constBegin(); it != MctVehicleDataMap.constEnd(); ++it) {
            stream << QString::fromStdString(it.value());
            if (it != MctVehicleDataMap.constEnd()) {
                stream << ",";
            }//end if
        }//end for that writes the data associated with the headers
        stream << "\n"; // create a new line

        file.close();

     }//end if that test if the file is WriteOnly or Text
     else
     {
        std::cerr << "Failed to open the file for writing";
        return -1;
     }// end else

     return 0;
}

void MctVehicleData::checkConfigXMLFile()
{
#ifdef Q_OS_WIN

     QString configDir ="C:\\TEMP\\COMPDIR\\MCTAware"; //The directory that store the config file

     QDir directoryWin(configDir);
         if(!directoryWin.exists())  //check if the directory exist
     {
            directoryWin.mkpath(configDir); // if it does not exist we create it
     }
     else
     {
            QMessageBox::critical(nullptr, "Error","Unable to create config file!");

     }

            QString WindowsFilePath = "C:\\TEMP\\COMPDIR\\MCTAware\\.config.xml";

            QFile file(WindowsFilePath);
            if(!file.exists())
            {
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::critical(nullptr, "Error", "Unable create config file!");
            }
            writeConfig(file);




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


