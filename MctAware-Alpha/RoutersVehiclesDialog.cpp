#include "RoutersVehiclesDialog.h"
#include <QVBoxLayout>

    RoutersVehiclesDialog::RoutersVehiclesDialog(const QString& routerCSVPath, const QString& vehicleCSVPath, QWidget *parent)
        : QDialog(parent)
    {
        // Set up the UI of the dialog
        QVBoxLayout* layout = new QVBoxLayout(this);
        tabWidget = new QTabWidget(this);
        layout->addWidget(tabWidget);

        // Create the widgets for each tab
        routerTableWidget = new QTableWidget(this);
        vehicleTableWidget = new QTableWidget(this);

        // Add the widgets to the tabs
        tabWidget->addTab(routerTableWidget, "Router CSV");
        tabWidget->addTab(vehicleTableWidget, "Vehicle CSV");

        // Read and display the contents of the router and vehicle CSV files
        QFile routerFile(routerCSVPath);
        if (routerFile.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&routerFile);
            int row = 0;
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList rowData = line.split(",");
                for (int col = 0; col < rowData.size(); ++col)
                {
                    QTableWidgetItem* item = new QTableWidgetItem(rowData[col]);
                    routerTableWidget->setItem(row, col, item);
                }
                ++row;
            }
            routerFile.close();
        }

        QFile vehicleFile(vehicleCSVPath);
        if (vehicleFile.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&vehicleFile);
            int row = 0;
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList rowData = line.split(",");
                for (int col = 0; col < rowData.size(); ++col)
                {
                    QTableWidgetItem* item = new QTableWidgetItem(rowData[col]);
                    vehicleTableWidget->setItem(row, col, item);
                }
                ++row;
            }
            vehicleFile.close();
        }
    }

    RoutersVehiclesDialog::~RoutersVehiclesDialog()
    {
        // Destructor
    }
