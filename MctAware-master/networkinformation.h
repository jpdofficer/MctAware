#ifndef NETWORKINFORMATION_H
#define NETWORKINFORMATION_H

#include<QString>
#include<QList>
#include<QNetworkInterface>
#include<QProcess>
#include<QDebug>
#include<QFileInfo>
#include<QRegularExpression>


#ifdef Q_OS_Windows
    #include<Windows.h>
#elif defined(Q_OS_LINUX)

#endif

class NetworkInformation
{
public:
    NetworkInformation();
    NetworkInformation(QList<QNetworkInterface> &NetInterface);
    //NetworkInformation(QVector<QNetworkInterface> &NetInterfaces);

    void setInterfaceVector();

    QVector<QNetworkInterface>getInterfaceVector();
    QMap<QString,QString> getAddressEntry();
    std::vector<QNetworkInterface> getInterfaceVectorStd();
    std::string arpMacAddress(std::string ipString); // returns the mac address of the interface
    std::string getDefaultIP(std::string selectedIf);
    std::string getSelectedIfMac(std::string mac);
    bool pingIPAddress(const QString & ipAddress);
    bool isVirtualInterface(QNetworkInterface const &);


private:
    QVector <QNetworkInterface> interfaceVector;
    QMap<QString,QString> addressEntries;



};

#endif // NETWORKINFORMATION_H
