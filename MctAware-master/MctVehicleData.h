#ifndef MCTVEHICLEDATA_H
#define MCTVEHICLEDATA_H

#include<iostream>
#include<chrono>
#include<ctime>
#include<QSysInfo>
#include<string>
#include<map>
#include<QNetworkInterface>
#include <QStandardPaths>
#include <QDir>
#include<QProcess>
#include<QRegularExpression>
#include<QOperatingSystemVersion>
#include<QXmlStreamWriter>
#include<QMessageBox>
#include<memory.h>
#include "networkinformation.h"
#include "computerinformation.h"
#include "modem.h"


#define MAX_SIZE 13

class MctVehicleData
{
    private:
    QMap<std::string, std::string>MctVehicleDataMap;
    std::unique_ptr<NetworkInformation> myNet;
    std::unique_ptr<ComputerInformation> myComputer;
    std::unique_ptr<Modem>myModem;

    public:
        MctVehicleData();
        MctVehicleData(QFile &file);
        void autoTimeStamp();
        void autoUserName();
        void autoComputerName();
        void autoComputerMacAddress();
        void autoComputerIP();
        void autoRouterMac();
        void autoRouterIP(std::string routerIP);

        void setUserName(std::string uname);
        void setComputerName(std::string compName);
        void setComputerMacAddress(std::string computerMac);
        void setComputerIP(std::string computerIP);
        void setRouterName(std::string routerName);
        void setRouterMac(std::string routerMac);
        void setRouterIP(std::string routerIP);
        void setRouterSerial(std::string routerSerial);
        void setRouterState(std::string routerState);
        void setRouterCSVPath(std::string routerCSVPath);
        void setMCTVehicleCSVPath(std::string mctVehiclePath);
        void setInterface(std::string interface);
        void setIMEI();
        void setIMSI();
        void setNumber();
        void setICCID();


        std::string getTimeStamp();
        std::string getUserName();
        std::string getComputerName();
        std::string getComputerMacAddress();
        std::string getComputerIP();
        std::string getRouterName();
        std::string getRouterMac();
        std::string getRouterIP();
        std::string getRouterSerial();
        std::string getRouterState();
        std::string getRouterCSVPath();
        std::string getMCTVehicleCSVPath();
        std::string getInterface();
        std::string getIMEI();
        std::string getIMSI();
        std::string getNumber();
        std::string getICCID();


        void checkConfigXMLFile();
        void writeConfig(QFile & file);
        int createCSV();








};


#endif // MCTVEHICLEDATA_H
