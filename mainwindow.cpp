#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*mainLayout = new QGridLayout(); // create a GridLayout
    QWidget *centralWidget = new QWidget(); //create a widget
    centralWidget ->setLayout(mainLayout); //from the centralWidget set the layout to mainLayout
    setCentralWidget(centralWidget); //set the main window to centralwidget
    setWindowTitle("MctVehicle");
    setFixedSize(360,200);*/

    QFile file("mainwindow.ui");
    file.open(QFile::ReadOnly);










}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Router_IPEdit_textChanged(const QString &ip)
{



        if(!ip.isEmpty())
        {
            ipaddress = ip;
            myData.setIpAddress(ipaddress);
        }

}

void MainWindow::on_Router_Button_clicked()
{
    QString routerFilePath = fileDialog->getOpenFileName();
    if(!routerFilePath.isEmpty())
    {

        routerCSV = routerFilePath;

    }
    //fileDialog = nullptr;
}


void MainWindow::on_Association_Button_clicked()
{
    QString filePath = fileDialog->getOpenFileName();
    if(!filePath.isEmpty())
    {
        associationCSV = filePath;


    }
    //fileDialog = nullptr;
}


void MainWindow::on_Submit_Button_clicked()
{

    myData.setRouterCSV(routerCSV);
    myData.setDataCSV(associationCSV);

    QApplication::quit();
}


void MainWindow::on_Network_Button_clicked()
{

    interfaceVector = QVector<QNetworkInterface>::fromList(QNetworkInterface::allInterfaces()); // get all interfaces and store them in interface vector
    showNetworkInterfaces();
}


void MainWindow::showNetworkInterfaces()
{
    // Create a QTableWidget and set the column count and headers
    QTableWidget* tableWidget = new QTableWidget;
    tableWidget->setColumnCount(4);
    QStringList headers = { "Name", "IP Address", "Connected", "Can Ping" };
    tableWidget->setHorizontalHeaderLabels(headers);

    // Set the row count based on the number of network interfaces
    int rowCount = interfaceVector.size();
    tableWidget->setRowCount(rowCount);

    // Populate the table with network interface details
    for (int row = 0; row < rowCount; ++row) {
        const QNetworkInterface& interface = interfaceVector[row];

        // Set the interface name
        QTableWidgetItem* nameItem = new QTableWidgetItem(interface.name());
        tableWidget->setItem(row, 0, nameItem);

        // Get the IP address and add it to the table
        QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();
        QString ipAddress;
        if (!addressEntries.isEmpty()) {
            ipAddress = addressEntries.first().ip().toString();
        }
        QTableWidgetItem* ipAddressItem = new QTableWidgetItem(ipAddress);
        tableWidget->setItem(row, 1, ipAddressItem);

        // Check connection status
        bool isConnected = interface.flags().testFlag(QNetworkInterface::IsUp) &&
                           !interface.flags().testFlag(QNetworkInterface::IsLoopBack);
        QString connectedStatus = isConnected ? "Yes" : "No";
        QTableWidgetItem* connectedItem = new QTableWidgetItem(connectedStatus);
        tableWidget->setItem(row, 2, connectedItem);

        if(!connectedStatus.contains("No") && !isVirtualInterface(interface))
        {
            // Ping the supplied address from MyData
            QString ipAddressToPing = QString::fromStdString(myData.getIpAddress());
            QProcess pingProcess;
            QString pingCommand;
            bool canPing;

            #ifdef Q_OS_WIN
            pingCommand = "ping -n 1 " + ipAddressToPing;
            #else
            pingCommand = "ping -c 1 " + ipAddressToPing;
            #endif


            //QString pingCommand = "ping -c 1 " + ipAddressToPing;
            pingProcess.start(pingCommand);
            pingProcess.waitForFinished();
            QByteArray pingResult = pingProcess.readAll();
            if(pingResult.contains("Reply from " + ipAddressToPing.toUtf8()) || pingResult.contains("bytes from " + ipAddressToPing.toUtf8()) )
                canPing = true;
            else
                canPing = false;
            //bool canPing =pingResult.indexOf(ipAddressToPing.toUtf8()) != -1;
            QString pingStatus = canPing ? "Yes" : "No";
            QTableWidgetItem* pingItem = new QTableWidgetItem(pingStatus);
            tableWidget->setItem(row, 3, pingItem);
        }
        else
        {
            QString pingStatus = "No";
            QTableWidgetItem* pingItem = new QTableWidgetItem(pingStatus);
            tableWidget->setItem(row, 3, pingItem);
        }
    }

    // Resize the columns to fit the content
    tableWidget->resizeColumnsToContents();

    // Create a dialog to display the table
    QDialog dialog;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(tableWidget);
    dialog.setLayout(layout);
    dialog.setWindowTitle("Network Interfaces");
    dialog.exec();

    // Clean up
    delete tableWidget;
}

// Function to check if the interface is virtual
bool MainWindow::isVirtualInterface(const QNetworkInterface& interface)
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
    }
#elif defined(Q_OS_LINUX)
    QString interfacePath = QString("/sys/class/net/%1/device/driver").arg(interface.name());

    // Linux-specific check for virtual interfaces
    QFileInfo driverInfo(interfacePath);
    if (driverInfo.isSymLink()) {
        QString driverName = driverInfo.symLinkTarget();
        if (driverName.contains("virtio") ||
            driverName.contains("veth") ||
            driverName.contains("vbox") ||
            driverName.contains("docker") ||
            driverName.contains("tun") ||
            driverName.contains("vmnet") ||
            driverName.contains("tap")) {
            return true;
        }
    }
#endif

    return false;
}



