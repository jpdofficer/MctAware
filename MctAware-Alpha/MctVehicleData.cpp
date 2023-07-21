#include "MctVehicleData.h"

MctVehicleData::MctVehicleData()
{
    autoTimeStamp();
    setRouterIP("192.168.0.1");
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
    #ifdef Q_OS_WIN //windows specific code
        #include <windows.h>
        #include <wbemidl.h>
        #pragma comment(lib, "wbemuuid.lib")

    HRESULT hr;

    // Initialize COM
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        // Handle initialization error
       QMessageBox::critical(nullptr, "Error", "Unable to initalize COM!");
        return;
    }

    // Initialize security
    hr = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL);
    if (FAILED(hr))
    {
        // Handle security initialization error
        CoUninitialize();
       QMessageBox::critical(nullptr, "Error", "Security initalization Error!");
        return;
    }

    IWbemLocator* pLoc = NULL;
    IWbemServices* pSvc = NULL;
    IEnumWbemClassObject* pEnumerator = NULL;

    // Connect to WMI
    hr = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        reinterpret_cast<LPVOID*>(&pLoc));
    if (FAILED(hr))
    {
        // Handle WMI connection error
        CoUninitialize();
        QMessageBox::critical(nullptr, "Error", "WMI Connection Error!");
        return;
    }

    // Connect to the root\cimv2 namespace
    hr = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc);
    if (FAILED(hr))
    {
        // Handle namespace connection error
        pLoc->Release();
        CoUninitialize();
        QMessageBox::critical(nullptr, "Error", "Namespace Connection Error!");
        return;
    }

    // Set the security level on the proxy
    hr = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE);
    if (FAILED(hr))
    {
        // Handle proxy security error
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return QString();
    }

    // Query for the Win32_Process class
    hr = pSvc->ExecQuery(
        _bstr_t(L"WQL"),
        _bstr_t(L"SELECT * FROM Win32_Process WHERE Name='explorer.exe'"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);
    if (FAILED(hr))
    {
        // Handle query error
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        QMessageBox::critical(nullptr, "Error", "Unable to execute Query!");
        return;
    }

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    // Get the first instance of Win32_Process
    hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
    if (SUCCEEDED(hr) && uReturn > 0)
    {
        VARIANT var;
        CIMTYPE type;

        // Get the owner property of the process
        hr = pclsObj->Get(L"GetOwner", 0, &var, &type, NULL);
        if (SUCCEEDED(hr))
        {
            // Extract the username
            QString userName = QString::fromWCharArray(var.bstrVal);

            // Cleanup
            VariantClear(&var);
            pclsObj->Release();
            pEnumerator->Release();
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();

            MctVehicleDataMap["user_name "] =  userName;
        }
    }

    // Cleanup in case of failure
    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

      MctVehicleDataMap["user_name "] =  QString(); // Return empty string if user name is not found


    #elif defined(Q_OS_LINUX)
    /*char* loginName = std::getenv("LOGNAME");
    if (loginName)
    {
        MctVehicleDataMap["user_name "] = QString::fromUtf8(loginName).toStdString();
    }*/
    QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString userName = homePath.section(QDir::separator(), -1);

    setUserName(userName.toStdString());
    #endif


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
    try {
        // Run the 'arp' command to get the MAC address of the router
        QString routerIP = QString::fromStdString(getRouterIP()); // Replace with the appropriate method to get the router IP address
        QString arpCommand = "arp -n " + routerIP;
        QProcess arpProcess;
        arpProcess.start(arpCommand);
        arpProcess.waitForFinished();

        // Read the output of the 'arp' command
        QByteArray arpResult = arpProcess.readAll();
        QString arpOutput = QString::fromLocal8Bit(arpResult);

        // Parse the output to extract the MAC address
        QStringList arpLines = arpOutput.split('\n');
        QString routerMAC;
        for (const QString& line : arpLines) {
            QStringList columns = line.trimmed().split(QRegularExpression("\\s+"));
            if (columns.size() >= 3 && columns[0] == routerIP) {
                routerMAC = columns[2];
                break;
            }
        }

        // Update the router MAC address in your data structure
        MctVehicleDataMap["router_mac"] = routerMAC.toStdString();
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
    MctVehicleDataMap["router_mac"] = routerMac;
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



