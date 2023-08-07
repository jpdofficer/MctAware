#include "networkinformation.h"

/*NetworkInformation()
 * creates the interface vector
 *
 */
NetworkInformation::NetworkInformation()
{
    interfaceVector = QVector<QNetworkInterface>::fromList(QNetworkInterface::allInterfaces());
   for (const QNetworkInterface& interface : interfaceVector)
    {
        QList<QNetworkAddressEntry> entries = interface.addressEntries();
        for (const QNetworkAddressEntry& entry : entries)
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                addressEntries[interface.name()] = entry.ip().toString();
                break; // Assuming each interface has at most one IPv4 address
            }
        }
    }
}

NetworkInformation::NetworkInformation(QList<QNetworkInterface>& NetInterface)
{
    interfaceVector = QVector<QNetworkInterface>::fromList(NetInterface);
    for (const QNetworkInterface& interface : interfaceVector)
    {
        QList<QNetworkAddressEntry> entries = interface.addressEntries();
        for (const QNetworkAddressEntry& entry : entries)
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                addressEntries[interface.name()] = entry.ip().toString();
                break; // Assuming each interface has at most one IPv4 address
            }
        }
    }
}

NetworkInformation::NetworkInformation(QVector<QNetworkInterface>& NetInterfaces)
{
    interfaceVector = NetInterfaces;
    for (const QNetworkInterface& interface : interfaceVector)
    {
        QList<QNetworkAddressEntry> entries = interface.addressEntries();
        for (const QNetworkAddressEntry& entry : entries)
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                addressEntries[interface.name()] = entry.ip().toString();
                break; // Assuming each interface has at most one IPv4 address
            }
        }
    }
}



QVector<QNetworkInterface> NetworkInformation::getInterfaceVector()
{
    return this->interfaceVector;
}

QMap<QString,QString> NetworkInformation::getAddressEntry()
{

    return this->addressEntries;

}


//Returns the inteface vector via a std::vector
std::vector<QNetworkInterface> NetworkInformation::getInterfaceVectorStd()
{
    return std::vector<QNetworkInterface>(interfaceVector.begin(), interfaceVector.end());

}

bool NetworkInformation::pingIPAddress(const QString & ipAddress)
{
    QProcess pingProcess;
    QString pingCommand;
    QStringList pingArguments;
    bool canPing;

    #ifdef Q_OS_WIN
        pingCommand = "ping";
        pingArguments << "-n" <<  "1" << ipAddress;
    #else
        pingCommand = "ping";
        pingArguments << "-c" <<  "1" <<  ipAddress;
    #endif


    //QString pingCommand = "ping -c 1 " + ipAddressToPing;
    pingProcess.start("ping", pingArguments);
    pingProcess.waitForFinished();
    QByteArray pingResult = pingProcess.readAll();

    if(pingResult.contains("Reply from " + ipAddress.toUtf8()) || pingResult.contains("bytes from " + ipAddress.toUtf8()) )
        canPing = true;
    else
        canPing = false;

    return canPing;
}

bool NetworkInformation::isVirtualInterface(const QNetworkInterface& interface)
{
#ifdef Q_OS_WIN
    QString interfaceName = interface.name().toLower();

    // Windows-specific check for virtual interface names
    if (interfaceName.startsWith("virtual") ||
        interfaceName.startsWith("vmware") ||
        interfaceName.startsWith("tunnel") ||
        interfaceName.startsWith("ppp") ||
        interfaceName.startsWith("vmnet") ||
        interfaceName.startsWith("ppoe")) {
        return true;

#elif defined(Q_OS_LINUX)
    QString interfacePath = QString("/sys/class/net/%1/device/driver").arg(interface.name());

    // Linux-specific check for virtual interfaces
    QFileInfo driverInfo(interfacePath);
    if (driverInfo.isSymLink())
    {
        QString driverName = driverInfo.symLinkTarget();
        if (driverName.contains("virtio") ||
            driverName.contains("veth") ||
            driverName.contains("vbox") ||
            driverName.contains("docker") ||
            driverName.contains("tun") ||
            driverName.contains("vmnet") ||
            driverName.contains("tap"))
        {
            return true;
        }
    }

#endif

        return false;
    }


    std::string NetworkInformation::arpMacAddress( std::string ipString)
    {

        try {
            // Run the 'arp' command to get the MAC address of the router
            QString routerIP = QString::fromStdString(ipString); // Replace with the appropriate method to get the router IP address

            QProcess arpProcess;
            arpProcess.start("arp", QStringList() << "-n" << routerIP);
            arpProcess.waitForFinished();

            // Read the output of the 'arp' command
            QByteArray arpResult = arpProcess.readAll();
            QString arpOutput = QString::fromLocal8Bit(arpResult);

            // Parse the output to extract the MAC address
            QStringList arpLines = arpOutput.split('\n');
            QRegularExpression regex("\\s+");
            QString routerMAC;
            for (const QString& line : arpLines) {
                QStringList columns = line.trimmed().split(regex);
                if (columns.size() >= 3 && columns[0] == routerIP) {
                    routerMAC = columns[2];
                    break;
                }
            }

            // Update the router MAC address in your data structure
            // MctVehicleDataMap["router_mac"] = routerMAC.toStdString();
            return routerMAC.toStdString();
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


