#ifndef MODEM_H
#define MODEM_H
#include<QString>
#include<QList>
#include <QtCore/QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include<memory>
#include<iostream>

class Modem
{
public:
    Modem();
    int initalizeModem();
    void setIMEI();
    void setIMSI();
    void setNumber();
    void setICCID();
    void closeModem();

    QString getIMEI();
    QString getIMSI();
    QString getNumber();
    QString getICCID();

private:
    std::unique_ptr<QMap<QString,QString>> modemInfo; // store all values of
    QList<QSerialPortInfo> serialPorts;
    QSerialPortInfo serialPortInfo;
    QSerialPort modemSerialPort;
};

#endif // MODEM_H
