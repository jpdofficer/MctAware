#include "mainwindow.h"

#include <QApplication>
#include<iostream>
#include<memory>
#include<QOperatingSystemVersion>
#include<QMessageBox>
#include<QDebug>
#include<QDir>
#include "mctvehiclecheck.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MctVehicleCheck mctvc;



#ifdef Q_OS_Win

    QString WindowsFilePath = "C:\TEMP\COMPDIR\MCTAware\.config.xml";

    QFile file(WindowsFilePath);
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(nullptr, "Error", "Unable create config file!");
        }
    }
    else
    {
        std::unique_ptr<MainWindow> w(new MainWindow);
        w->show();
        return a.exec();
    }

#elif defined(Q_OS_LINUX)

    QString linuxFilePath = "/home/jyeager/Temp/MctAware/.config.xml";
    QFile file(linuxFilePath);
        if(file.exists())
        {
            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
               // QMessageBox::critical(nullptr, "Error", "File Exist!");
                MctVehicleCheck  mctvc = MctVehicleCheck(linuxFilePath);
               mctvc.readLocalConfig();
            }
        }
        else
        {
            std::unique_ptr<MainWindow> w(new MainWindow);
            w->show();
            return a.exec();
        }

#else

        QMessageBox(nullptr,"Error","Unsupported Operating System");

#endif

}
