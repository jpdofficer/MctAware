/*Computer information
 * A C++ class that gets all the computers information
 * It gets the computers identification, a asset tag, operating system, machine name, form factor, motherboard, ram installed, hard drives installed, serial ports, com ports
 * lpt ports,
 *
 *
 */
#ifndef COMPUTERINFORMATION_H
#define COMPUTERINFORMATION_H

#include<memory>

#include "networkinformation.h"

class ComputerInformation
{
public:
    ComputerInformation();

    void setComputerID();
    void setComputerAssetTag();
    void setOperatingSystem();
    void setMachineName();
    void setFormFactor();
    void setComputerID(QString id);
    void setComputerAssetTag(QString asset);
    void setMachineName(QString host);
    void setOperatingSystem(QString os);


    QString getComputerID();
    QString getComputerAssetTag();
    QString getOperatingSystem();
    QString getMachineName();
    QString getFormFactor();
    QMap<QString,QString> getNetworkInterfaces();

private:
    std::unique_ptr< QMap<QString,QString>> computerInfo;
    std::unique_ptr<NetworkInformation> netInfo;


};

#endif // COMPUTERINFORMATION_H
