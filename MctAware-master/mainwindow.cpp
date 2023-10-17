#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    QFile file("mainwindow.ui"); // this is the xml file that stores all the data to show the window
    file.open(QFile::ReadOnly); // make sure we open this as read only
    QAction* actionView_Routers = new QAction("View Routers", this); // the action viewer is when someone clicks on this it shows all available routers
    connect(actionView_Routers, &QAction::triggered, this, &MainWindow::on_View_Routers); // this is the connection to the action_routers method that shows the routers

    fileDialog = new QFileDialog(this); // create a new fileDialog
    myNet = std::make_unique<NetworkInformation>(); // create a unique pointer to network information notice new classes will remove this
    mctData = std::make_unique<MctVehicleData>(); // mctdata is where I store all the data about the vehicle and mct interface
    computer = std::make_unique<ComputerInformation>(); // Create a new computer
    routerPtr = std::make_unique<CradlePointRouter>(); //router pointer is a pointer to the router information
    myModem = std::make_unique<Modem>();
    myNet = std::make_unique<NetworkInformation>();
    ui->menuFile->addAction(actionView_Routers); // we add a menu here so you will pick to view the routers


}

//setNetworkInterface: sets the network interfaces
void MainWindow::setNetworkInterface(QString netInterface )
{
    //myData.setNetwork(netInterface);
    this->networkInterface  = netInterface;

}

//setIpAddress: Sets the ip address
void MainWindow::setIpAddress(QString ip)
{
    this->ipaddress = ip;
}
//setRouterCSV: Sets the router CSV
void MainWindow::setRouterCSV(QString rcsv)
{
    this->routerCSV = rcsv;

}
//setAssoCSV: Sets the Association CSV
void MainWindow::setAssoCSV(QString assoc)
{
    this->associationCSV = assoc;
}

//getNetworkInterface: Gets the network Interface
std::string MainWindow::getNetworkInterface()
{
    return this->networkInterface.toStdString(); //return the network interface as a Standard String
}

//getIpAddress: Gets the ipaddress
std::string MainWindow::getIpAddress()
{
    return this->ipaddress.toStdString();
}
//getRouterCSV: gets the routers csv
std::string MainWindow::getRouterCSV()
{
    return this->routerCSV.toStdString();
}

//getAssoCSV: gets the association CSV
std::string MainWindow::getAssoCSV()
{
    return this->associationCSV.toStdString();
}

//on_View_Routers: shows the routers from the file view routers
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
        RoutersVehiclesDialog routerDialog(routerCSVPath, vehicleCSVPath, this);
        routerDialog.exec();
    }
}

//on_Router_IPEdit_textChangeed: Sets the ip address to the one provided in a textbox
void MainWindow::on_Router_IPEdit_textChanged(const QString &ip)
{



    if(!ip.isEmpty())
    {
        setIpAddress(ip);
       // mctData ->setRouterIP(ipaddress.toStdString());
    }

}


//on_Router_Button_Clicked: Once the router button is clicked it presents a dialog that shows the router csv
void MainWindow::on_Router_Button_clicked()
{
    QString routerFilePath = QFileDialog::getOpenFileName(this, "Open Router CSV", QString(), "CSV Files (*.csv)");
    if(!routerFilePath.isEmpty())
    {

        routerCSV = routerFilePath;
        routerPtr->setRouterFile(routerFilePath);

    }
    //fileDialog = nullptr;
}

void MainWindow::on_Network_Button_clicked()
{

    interfaceVector = QVector<QNetworkInterface>::fromList(QNetworkInterface::allInterfaces()); // get all interfaces and store them in interface vector
    this->showNetworkInterfaces();
}



/*showNetworkInterfaces
 * Returns a Dialog box that allows the user to select the interface in which to use to connect to the router
 *
 */

QString MainWindow::showNetworkInterfaces()
{
    // Create a QTableWidget and set the column count and headers
    QTableWidget* tableWidget = new QTableWidget; //create a new tableWidget
    tableWidget->setColumnCount(4); //set The column count to 4
    QStringList headers = { "Name", "IP Address", "Connected", "Can Ping" }; //name the Headers
    tableWidget->setHorizontalHeaderLabels(headers); // place the headers into the the TableWidget with SetHorizontalHeadersLabel



    // Filter network interfaces to include only Ethernet and Wi-Fi
    QVector<QNetworkInterface> filteredInterfaces;
    for (int i = 0; i < myNet->getInterfaceVector().size(); ++i) { // loop through all the interfaces
        const QNetworkInterface& interface = interfaceVector.at(i);  // set the interface to the Interface vector at the count
        if ((interface.type() == QNetworkInterface::Ethernet ||   // if the interface is EtherNet or WiFi or Iee80211(wifi) and the interface is not virtual( doesnt really seem to have to do with VM's) or unknown
             interface.type() == QNetworkInterface::Wifi ||
             interface.type() == QNetworkInterface::Ieee80211)  &&
            (interface.type() != QNetworkInterface::Virtual ||
             interface.type() != QNetworkInterface::Unknown))
        {
            filteredInterfaces.append(interface);  //we Append the interface list to the filtered interfaces
        }
    }




    // Set the row count based on the number of network interfaces
    int rowCount = filteredInterfaces.size(); //get the size of the filteredInterfaces
    tableWidget->setRowCount(rowCount);  // We now set how many rows will be in the table widget

    // Populate the table with network interface details
    for (int row = 0; row < rowCount; ++row) //loop through the filteredInterfaces and go one interface at a time
    {

        const QNetworkInterface& interface = filteredInterfaces.at(row);  // get the interface at the rowCount

        // Set the interface name
        QTableWidgetItem* nameItem = new QTableWidgetItem(interface.humanReadableName()); // set the name of the interface, in humanReadble format
        tableWidget->setItem(row, 0, nameItem); // We are going to set that at TableWidget rowCount, column 0, and the name of the interface

        // Get the IP address and add it to the table
        QMap<QString, QString> addressEntries = myNet->getAddressEntry(); // get all entries from the NetworkInformation
        for (int row = 0; row < rowCount; ++row)  //for row is 0 till row < row count add one to row
        {
            const QNetworkInterface& interface = filteredInterfaces.at(row); // get only the rows based off the filtered interfaces
            QString interfaceName = interface.name();     //get the interface name

            // Check if the interface name exists in the addressEntries map
            if (addressEntries.contains(interfaceName))  // if addressEntries contains the interface
            {
                QString ipAddress = addressEntries.value(interfaceName); // get the value associated with the key in QMap intefaceName

                QTableWidgetItem* ipAddressItem = new QTableWidgetItem(ipAddress); // place the address in the QTableWidgetItem
                tableWidget->setItem(row, 1, ipAddressItem); //set it at the row count, 1st column, and then the IP address
            }
            else
            {
                QTableWidgetItem* ipAddressItem = new QTableWidgetItem("N/A"); // if there is no IP associated with the interface put in N/A
                tableWidget->setItem(row, 1, ipAddressItem);//set it at the row count, 1st column, and then the IP address
            }


        }


        // Check connection status
        bool isConnected = interface.flags().testFlag(QNetworkInterface::IsUp) &&  //chect if the Interface is connected and is not Loopback
                           !interface.flags().testFlag(QNetworkInterface::IsLoopBack);
        QString connectedStatus = isConnected ? "Yes" : "No"; // if it is connected Return Yes( though I would like to make this a visual button like green for yes and red for no
        QTableWidgetItem* connectedItem = new QTableWidgetItem(); // Add this to the TableWidgetItem Que
        if(isConnected)
        {
            connectedItem ->setData(Qt::DecorationRole,QPixmap(":/Images/check.png"));

        }
        else
        {
             connectedItem->setData(Qt::DecorationRole, QPixmap(":/Images/x.png"));
        }
        tableWidget->setItem(row, 2, connectedItem); // place this on the row count, column number 2, with the ConnectedItem( the status

        //Test if we can ping the supplied IP address
        bool canPing = false; //Set it to false not assuming that we can ping the ip address
        if(!connectedStatus.contains("No") && !myNet->isVirtualInterface(interface)) // if the connected states does not contains No and ins not a virtualInterface
        {
            // Ping the supplied address from MyData
             QString ipAddressToPing = QString::fromStdString(this->ipaddress.toStdString()); //get the ipAddress to ping from the ipaddress
            canPing = myNet->pingIPAddress(ipAddressToPing); // call myNet pingIPAddress which performs the pin

             QTableWidgetItem* pingItem = new QTableWidgetItem();
             if (canPing) {
                // If canPing is true, set the check mark image
                pingItem->setData(Qt::DecorationRole, QPixmap(":/Images/check.png"));
             } else {
                // If canPing is false, set the X image
                pingItem->setData(Qt::DecorationRole, QPixmap(":/Images/x.png"));
             }

           // QString pingStatus = canPing ? "Yes" : "No"; // if you can ping put yes( again thinking about a button here) if no put no
            //QTableWidgetItem* pingItem = new QTableWidgetItem(pingStatus); // add it to the widget item que
            tableWidget->setItem(row, 3, pingItem); // place it in row count, column 3 and ping count
        }
        else
        {
            //QString pingStatus = "No"; //else put no
            QTableWidgetItem* pingItem = new QTableWidgetItem();
            pingItem->setData(Qt::DecorationRole, QPixmap(":/Images/x.png"));
            tableWidget->setItem(row, 3, pingItem);
        }
    }

    // Resize the columns to fit the content
    tableWidget->resizeColumnsToContents();



    // Create a dialog to display the table
    QDialog dialog; //create a dialog to display the table
    dialog.resize(450,200); //set the size to 450,200
    QVBoxLayout* layout = new QVBoxLayout; // make it a box layout
    layout->addWidget(tableWidget); // we are going to add the tableWidget to the box layout
    dialog.setLayout(layout); // we set t he dialog to the QVBoxLayout
    dialog.setWindowTitle("Network Interfaces"); //set the Title to Network Interfaces

    // Add a selection button
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel); // create a button that is the QDialogBoxButton and set the Buttons to Ok and Cancle
    layout->addWidget(buttonBox); // add this to the layout

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept); // connect to buttonBox which handles the button, pass accepted
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Execute the dialog
    if (dialog.exec() == QDialog::Accepted)
    {
        QModelIndexList selectedIndexes = tableWidget->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty())
        {
            int selectedRow = selectedIndexes.first().row();
            const QNetworkInterface& selectedInterface = filteredInterfaces[selectedRow];
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

    computer ->setOperatingSystem();
    computer ->setMachineName();
    computer->getNetworkInterfaces();
    computer->setFormFactor();
    myNet -> getDefaultIP(getNetworkInterface());
    myNet -> getSelectedIfMac(getNetworkInterface());
    myModem->initalizeModem();
    myModem->setIMEI();
    myModem->setIMSI();
    myModem->setNumber();
    myModem->setICCID();
    mctData->setRouterIP(getIpAddress());
    mctData->setRouterCSVPath(getRouterCSV());
    mctData->setInterface(getNetworkInterface());
    mctData->setMCTVehicleCSVPath(getAssoCSV());
    mctData->autoUserName();
    mctData->setComputerName(computer->getMachineName().toStdString());
   // mctData->autoComputerIP();
    mctData->setIMEI();
    mctData->setIMSI();
    mctData->setNumber();
    mctData->setICCID();
    mctData->autoRouterMac();
    mctData->autoComputerMacAddress();
    mctData->checkConfigXMLFile();
    mctData->createCSV();



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
