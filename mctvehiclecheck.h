#ifndef MCTVEHICLECHECK_H
#define MCTVEHICLECHECK_H
#include<QFile>
#include<QXmlStreamReader>
#include<QMessageBox>
#include<memory>
#include"MctVehicleData.h"

class MctVehicleCheck
{
public:
    MctVehicleCheck(const QString & xmlFilesmptr);
    void readLocalConfig(); //reads the XML File

private:
    std::unique_ptr<QFile> xmlFile; // a pointer to the QFile
    std::unique_ptr<MctVehicleData> xmlData; // a pointer to mctvehicledata
};

#endif // MCTVEHICLECHECK_H
