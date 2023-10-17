#include "modem.h"

Modem::Modem(){

    modemInfo = std::make_unique<QMap<QString,QString>>();
}

int  Modem::initalizeModem()
{

   // Find available serial ports
    serialPorts = QSerialPortInfo::availablePorts();
    if (serialPorts.isEmpty()) {
        qDebug() << "No serial ports found.";
        return 1;
    }

        // Select the first available serial port
    serialPortInfo = serialPorts.first();


    modemSerialPort.setPort(serialPortInfo);
    modemSerialPort.setBaudRate(QSerialPort::Baud9600);
    modemSerialPort.setDataBits(QSerialPort::Data8);
    modemSerialPort.setParity(QSerialPort::NoParity);
    modemSerialPort.setStopBits(QSerialPort::OneStop);
    modemSerialPort.setFlowControl(QSerialPort::NoFlowControl);

   if (!modemSerialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open modem on" << serialPortInfo.portName();
        return 1;
    } //end initalizeModem

   modemSerialPort.write("ATE0\r\n"); // Turn off echo
   if (modemSerialPort.waitForReadyRead(3000)) {
        std::cout << "\nModem response after ATE0:" << modemSerialPort.readAll().trimmed().toStdString();
   } else {
        std::cout << "Failed to receive response after ATE0.";
   }

   // Check if SIM card is ready
   modemSerialPort.write("AT+CPIN?\r\n");
   if (modemSerialPort.waitForReadyRead(3000)) {
        QString cpinResponse = modemSerialPort.readAll().trimmed();
        if (cpinResponse.contains("+CPIN: READY")) {
            qDebug() << "SIM card is ready. Proceed to retrieve information.";

            // Here you can proceed to retrieve IMEI, IMSI, ICCID, etc.
        } else {
            qDebug() << "SIM card is not ready.";
        }
   } else {
        qDebug() << "Failed to retrieve SIM card status.";
   }
   return 0;
}

void Modem::setIMEI()
{
   modemSerialPort.write("AT+GSN\r\n");
   if (modemSerialPort.waitForReadyRead(3000)) {
        //std::cout << "\nIMEI:" << modemSerialPort.readAll().trimmed().toStdString();
        (*modemInfo)["IMEI"]  = modemSerialPort.readAll().trimmed();
   } else {
        (*modemInfo)["IMEI"] = "Failed to retrieve IMEI.";
   }
}
void Modem::setIMSI()
{

   // Send command to retrieve IMSI
   modemSerialPort.write("AT+CIMI\r\n");
   if (modemSerialPort.waitForReadyRead(3000)) {
        (*modemInfo)["IMSI"] =  modemSerialPort.readAll().trimmed();
   } else {
        qDebug() << "Failed to retrieve IMSI.";
   }
}
void Modem::setNumber()
{

   //get the number
   modemSerialPort.write("AT+CNUM\r\n");
   if (modemSerialPort.waitForReadyRead(3000)) {
        (*modemInfo)["NUMBER"] = modemSerialPort.readAll().trimmed();
   } else {
        (*modemInfo)["NUMBER"] = "Failed to retrieve number.";
   }
}
void Modem::setICCID()
{
   modemSerialPort.write("AT+ICCID\r\n");
   if (modemSerialPort.waitForReadyRead(3000)) {
        (*modemInfo)["SIM_ICCID"] = modemSerialPort.readAll().trimmed();
   } else {
        (*modemInfo)["SIM_ICCID"] = "Failed to retrieve SIM ICCID.";
   }
}

QString Modem::getIMEI()
{
   return (*modemInfo)["IMEI"];
}
QString Modem::getIMSI()
{
   return(*modemInfo)["IMSI"];
}
QString Modem::getNumber()
{
   return(*modemInfo)["NUMBER"];
}
QString Modem::getICCID()
{
   return (*modemInfo)["SIM_ICCID"];
}


