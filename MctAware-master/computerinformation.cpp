#include <memory.h>
#include "computerinformation.h"


ComputerInformation::ComputerInformation()
{

    computerInfo = std::make_unique <QMap<QString,QString>>();
    netInfo = std::make_unique<NetworkInformation>();

}

void ComputerInformation::setComputerAssetTag(QString asset)
{
    (*computerInfo)["Asset"] = asset;
}

void ComputerInformation::setMachineName()
{
    (*computerInfo)["Computer_Name"] = QSysInfo::machineHostName();
}
void ComputerInformation::setOperatingSystem()
{
    (*computerInfo)["Operating_System"] = QSysInfo::prettyProductName();
}

QString ComputerInformation::getMachineName()
{
    return (*computerInfo)["Computer_Name"];
}
QMap<QString,QString> ComputerInformation::getNetworkInterfaces()
{
    return netInfo->getAddressEntry();
}

void ComputerInformation::setFormFactor()
{
    #ifdef Q_OS_WIN
        QProcess process;//call qprocss
        QString command = "powershell.exe"; //call powershell
        QStringList args; // any arguments to go along with it
        args << "-command" <<"Get-WmiObject -Class Win32_Battery"; // run this command in powershell
        process.start(command,args); // start the command with the argme

        //Capture the output
        QString output;
        // Connect a slot to the readyReadStandardOutput signal to capture the output
            QObject::connect(&process, &QProcess::readyReadStandardOutput, [&]() {
                output += process.readAllStandardOutput();
            });

        process.start();
        process.waitForFinished();

         bool batteryPresent = output.contains("BatteryStatus");

        //QString output = process.readAllStandardOutput();
        if (batteryPresent) {
            (*computerInfo)["Form_Factor"] = "Laptop";
        } else {
            (*computerInfo)["Form_Factor"] = "Desktop";
        }
#elif defined(Q_OS_LINUX)

        QString path = "/sys/class/power_supply/BATO /type";
        QFile file(path);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString type = file.readAll().trimmed();
            if (type == "Battery") {
                 (*computerInfo)["Form_Factor"] = "Laptop";
            }
        }

        (*computerInfo)["Form_Factor"] = "Desktop";
#endif

}

QString ComputerInformation::getFormFactor()
{
        return (*computerInfo)["Form_Factor"];
}
