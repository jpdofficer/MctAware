#include "mctvehiclecheck.h"

/*MctVehicleCheck(const QString& file)
 *A constructor that takes a QString named xmlFileSmptr and creates a smart pointer to a QFile then test that the pointer.
 *If the xmlFile does not exist we throw a std::runtime_error stating
 *
 *
 */
MctVehicleCheck::MctVehicleCheck(const QString& xmlFileSmptr)
    : xmlFile(std::make_unique<QFile>(xmlFileSmptr))
{

    if(!xmlFile->exists())
    {
         QMessageBox::critical(nullptr, "Error", "Failed to open file");
        throw std::runtime_error("Failed to create QFile object.");

    }
    xmlData = std::make_unique<MctVehicleData>();
    netInfo = std::make_unique<NetworkInformation>();

}

/*Read the local config file stored on the client system
 * This is called if there is a local configuration file
 * From there we call MctVehicleData which stores all the information
 * We set the ip, interface, cvs locations, and router mac address
 */
void MctVehicleCheck::readLocalConfig()
{
   try
    {
        if(!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(nullptr, "Error", "Failed to open the configuration file");
        }
        QXmlStreamReader xmlReader(xmlFile.get());

        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            if(xmlReader.isStartElement())
            {
                QString elementName = xmlReader.name().toString();
                if(elementName =="ip")
                {

                    xmlData->setRouterIP(xmlReader.readElementText().toStdString());

                }//end if(elementName =="ip")
                else
                if( elementName == "router_mac")
                {

                    //here I am going to test for a match if the router mac matchs what is in the config file we should be in the correct car
                    //if configRouterMac is equal to arpMacAddress
                    std::string testString = xmlReader.readElementText().toStdString();
                    //see if the mac address is the same in the config file and that the mac address != --
                    if(testString != "--" || testString != "")
                    {
                        if( testString == (netInfo->arpMacAddress(xmlData->getRouterIP())) )
                        {
                         xmlData ->setRouterMac(testString);
                        }//end if( testString.compare(netInfo->arpMacAddress(xmlData->getRouterIP())) == 0)
                        else
                        {
                         //display a message that mct is in the wrong vehicle
                         //check the router data and then get the vehicle number from the vehicle file
                         QMessageBox::critical(nullptr, "ERROR", "This MCT is in an unassigned Vehicle");
                         return;


                        }
                    }//end if(testString != "--")
                    else
                    {
                        QMessageBox::critical(nullptr, "ERROR", "No Mac in xml file");
                        return;
                    }
                }//end  else if( elementName == "router_mac")
                else
                if( elementName == "routerCvs")
                {
                    xmlData ->setRouterCSVPath(xmlReader.readElementText().toStdString());
                }
                else
                if( elementName == "interface")
                {
                    xmlData ->setInterface(xmlReader.readElementText().toStdString());
                    //here I am going to test if the interface matches what is in the config file
                    // test that the interface exist if it does can it ping the router
                    //if not display that the interface is incorrect
                }//end if(elementName == Interface)
                else
                if( elementName == "vehicleCvs")
                {
                    xmlData ->setMCTVehicleCSVPath(xmlReader.readElementText().toStdString());
                }
            }// end if(xmlReader.isStartElement())
            xmlReader.readNext();
        }//end while(!xmlReader.atEnd() && !xmlReader.hasError())

        if (xmlReader.hasError()) {
            throw std::runtime_error("XML parsing error: " + xmlReader.errorString().toStdString());
        }
   }//end try
   catch( std::exception &e)
   {
        QMessageBox::critical(nullptr, "ERROR", e.what());
   }
}

