#ifndef MCTDATA_H
#define MCTDATA_H

#include<QString>
#include <QDebug>

#include<string>

#include<iostream>
/**
 * @brief The MctData class
 * @author John Yeager
 * @copyright July 7th, 2023
 * @remark MctData is a class that stores the location of the routerCVS provided by the manufacturers of the product
 * @remark It also provides the network interface used
 * @remark and it provides where the user wishes to store this data.
 */


class MctData
{
    private:
        std::string ipAddress;  //stores the ipAddress
        std::string routerCSV; // this is the manufactuers csv file that list all their routers
        std::string networkInterface;// this is the network interface that connects to that router for example  Ethernet, Ethernet 2... or Wifi
        std::string dataCSV; // this is the location where the data from the router cvs and the computers name is stored into one file. Personally I would perfer this to be a sql database but have to use what we can
        //private functions
        void createXML(); // this creates the xml file, i wanted to use a xml file just in case I can move over to a database

    public:
        MctData();
        void setIpAddress(const QString ipaddress);
        void setRouterCSV(const QString RouterCSV); // set the location of the router csv
        void setNetwork(const QString NetworkInterface); //set the network interface
        void setDataCSV(const QString DataCSV); // set the dataCsv
        std::string getRouterCSV(); // get the router csv path
        std::string getNetwork(); // get the network interface used
        std::string getDataCSV(); // get the data csv
        std::string  getIpAddress();
        ~MctData();


};

#endif // MCTDATA_H
