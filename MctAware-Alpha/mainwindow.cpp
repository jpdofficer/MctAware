#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    QFile file("mainwindow.ui");
    file.open(QFile::ReadOnly);
 //   routerDialog = new RoutersVehiclesDialog("/home/jyeager/Downloads/routers.csv", "", this);
    QAction* actionView_Routers = new QAction("View Routers", this);
    connect(actionView_Routers, &QAction::triggered, this, &MainWindow::on_View_Routers);

    fileDialog = new QFileDialog(this);
    mctData = new MctVehicleData();
    // Add the "View Routers" action to the File menu
    ui->menuFile->addAction(actionView_Routers);


}


void MainWindow::setNetworkInterface(QString netInterface )
{
    //myData.setNetwork(netInterface);
    this->networkInterface  = netInterface;

}

void MainWindow::setIpAddress(QString ip)
{
    this->ipaddress = ip;
}

void MainWindow::setRouterCSV(QString rcsv)
{
    this->routerCSV = rcsv;
}
void MainWindow::setAssoCSV(QString assoc)
{
    this->associationCSV = assoc;
}

std::string MainWindow::getNetworkInterface()
{
    return this->networkInterface.toStdString(); //return the network interface as a Standard String
}

std::string MainWindow::getIpAddress()
{
    return this->ipaddress.toStdString();
}

std::string MainWindow::getRouterCSV()
{
    return this->routerCSV.toStdString();
}

std::string MainWindow::getAssoCSV()
{
    return this->associationCSV.toStdString();
}


void MainWindow::on_View_Routers()
{

    // Open the file dialog to select the router CSV file
    QString routerCSVPath =
        QFileDialog::getOpenFileName(this, "Open Router CSV", QString(), "CSV Files (*.csv)");
    QString vehicleCSVPath =
        QFileDialog::getOpenFileName(this, "Open Vehicle CSV", QString(), "CSV Files (*.csv)");
    if (!routerCSVPath.isEmpty())
    {
        // Create and show the RoutersVehiclesDialog with the selected router CSV file
        RoutersVehiclesDialog dialog(routerCSVPath, vehicleCSVPath, this);
        dialog.exec();
    }
}


void MainWindow::on_Router_IPEdit_textChanged(const QString &ip)
{



    if(!ip.isEmpty())
    {
        setIpAddress(ip);
       // mctData ->setRouterIP(ipaddress.toStdString());
    }

}



void MainWindow::on_Router_Button_clicked()
{
    QString routerFilePath = QFileDialog::getOpenFileName(this, "Open Router CSV", QString(), "CSV Files (*.csv)");
    if(!routerFilePath.isEmpty())
    {

        routerCSV = routerFilePath;

    }
    //fileDialog = nullptr;
}

void MainWindow::on_Network_Button_clicked()
{

    interfaceVector = QVector<QNetworkInterface>::fromList(QNetworkInterface::allInterfaces()); // get all interfaces and store them in interface vector
    this->showNetworkInterfaces();
}



QString MainWindow::showNetworkInterfaces()
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
        QTableWidgetItem* nameItem = new QTableWidgetItem(interface.humanReadableName());
        tableWidget->setItem(row, 0, nameItem);

        // Get the IP address and add it to the table
        QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();
        QString ipAddress;
        //if (!addressEntries.isEmpty()) {
        //    ipAddress = addressEntries.first().ip().toString();
        //}
        for (const QNetworkAddressEntry& entry : addressEntries) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                ipAddress = entry.ip().toString();
                break;
            }
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
            QString ipAddressToPing = QString::fromStdString(this->ipaddress.toStdString());
            QProcess pingProcess;
            QString pingCommand;
            QStringList pingArguments;
            bool canPing;

#ifdef Q_OS_WIN
            pingCommand = "ping";
            pingArguments << "-n" <<  "1" << ipAddressToPing;
#else
            pingCommand = "ping";
            pingArguments << "-c" <<  "1" <<  ipAddressToPing;
#endif


            //QString pingCommand = "ping -c 1 " + ipAddressToPing;
            pingProcess.start("ping", pingArguments);
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
    dialog.resize(450,200);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(tableWidget);
    dialog.setLayout(layout);
    dialog.setWindowTitle("Network Interfaces");

    // Add a selection button
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted) {
        QModelIndexList selectedIndexes = tableWidget->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty()) {
            int selectedRow = selectedIndexes.first().row();
            const QNetworkInterface& selectedInterface = interfaceVector[selectedRow];
            QString selectedName = selectedInterface.name();
            setNetworkInterface(selectedName);
            return selectedName;
        }
    }

    // Clean up
    delete tableWidget;

    // Return an empty QString if no interface was selected
    return QString();
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



void MainWindow::on_Association_Button_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Associations CSV", QString(), "CSV Files (*.csv)");
    if(!filePath.isEmpty())
    {
        associationCSV = filePath;


    }
    //fileDialog = nullptr;
}


void MainWindow::on_Submit_Button_clicked()
{

    mctData->setRouterIP(getIpAddress());
    mctData->setRouterCSVPath(getRouterCSV());
    mctData->setInterface(getNetworkInterface());
    mctData->setMCTVehicleCSVPath(getAssoCSV());
    mctData->autoUserName();
    mctData->autoComputerName();
    mctData->autoComputerIP();
    mctData->autoRouterMac();
    mctData->autoComputerMacAddress();



    QApplication::quit();
}











void MainWindow::on_Cancel_Button_clicked()
{
    QApplication::exit();
}


MainWindow::~MainWindow()
{
    delete ui;
}
