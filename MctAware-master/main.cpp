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



#ifdef Q_OS_WIN

    QString WindowsFilePath = "C:\\TEMP\\COMPDIR\\MCTAware\\.config.xml"; // location of the config file if this is a windows machine

    QFile file(WindowsFilePath); // make a reference to the file
    if(file.exists()) //if the file exisit we continue
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) //open the file for read only and that its a text file
        {
            //QMessageBox::critical(nullptr, "Error", "Unable create config file!"); //if we cannot open the file display this message
            MctVehicleCheck  mctvc = MctVehicleCheck(WindowsFilePath); // call to mctVehicleCheck which checks the linuxFIlePath, it basically reads if the xml file note this may change as we continue
            mctvc.readLocalConfig(); // read the config file
        }
    }
    else
    {
        std::unique_ptr<MainWindow> w(new MainWindow); //after we have the file and such create a new mainWindow
        w->show(); //show the window
        return a.exec(); // and return the executable
    }

#elif defined(Q_OS_LINUX)

    QString linuxFilePath = "/home/jyeager/Temp/MctAware/.config.xml"; //location of the linux file
    QFile file(linuxFilePath); // create a reference
        if(file.exists()) // if it exist
        {
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) //can we open it and an enumeration value used in Qt's IO classes to indicate that the data being read from or written to the device should be processed in text mode
            {
               // QMessageBox::critical(nullptr, "Error", "File Exist!");
                MctVehicleCheck  mctvc = MctVehicleCheck(linuxFilePath); // call to mctVehicleCheck which checks the linuxFIlePath, it basically reads if the xml file note this may change as we continue
               mctvc.readLocalConfig(); // read the config file
            }
        }
        else
        {
            std::unique_ptr<MainWindow> w(new MainWindow); // else we open a new window that will create the xml file
            w->show(); //show the window
            return a.exec(); // and execute
        }

#else

    QMessageBox::critical(nullptr,"Error","Unsupported Operating System"); // if this is a unsupported operating system we exit

#endif

}
