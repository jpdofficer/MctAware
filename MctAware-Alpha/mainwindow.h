#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * Header Name MainWindow_H
 * Purpose: To define the functions used by the main window
 *
 *
 */
#include <QMainWindow>
#include<QFileDialog>
#include <QFile>
#include<QDebug>
#include<iostream>
#include<QVector>
#include<QNetworkInterface>
#include<QTableWidget>
#include<QProcess>
#include<QDialogButtonBox>
#include<memory.h>

#include "MctVehicleData.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QString showNetworkInterfaces();
    bool isVirtualInterface(const QNetworkInterface& interface);
    std::string getNetworkInterface();
    void setNetworkInterface(QString netInterface );

    ~MainWindow();


private slots:
    void on_Router_Button_clicked();
    void on_Association_Button_clicked();
    void on_Submit_Button_clicked();
    void on_Network_Button_clicked();

    void on_Router_IPEdit_textChanged(const QString &arg1);

    void on_Cancel_Button_clicked();

private:
    Ui::MainWindow *ui;
    QString ipaddress;
    QString networkInterface;
    QString routerCSV;
    QString associationCSV;
    QVector<QNetworkInterface> interfaceVector;//create a vector to store all the Network Interfaces

    MctVehicleData mctData;
    QFileDialog *fileDialog; //creates a file dialog so that the user can select the correct files

};
#endif // MAINWINDOW_H
