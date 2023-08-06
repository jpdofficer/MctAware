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

}


void MctVehicleCheck::readLocalConfig()
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
                xmlData ->setRouterMac(xmlReader.readElementText().toStdString());
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
}
