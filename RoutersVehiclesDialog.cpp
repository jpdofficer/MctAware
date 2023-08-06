#include "RoutersVehiclesDialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug> // Add this include for debugging

RoutersVehiclesDialog::RoutersVehiclesDialog()
{

}

RoutersVehiclesDialog::RoutersVehiclesDialog(const QString& routerCSVPath, const QString& vehicleCSVPath, QWidget* parent)
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

    // Load and display the contents of the router and vehicle CSV files
    loadCSVData(routerCSVPath, routerTableWidget);
    loadCSVData(vehicleCSVPath, vehicleTableWidget);
    this->setMinimumSize(640, 480);

    routerTableWidget->update();
    vehicleTableWidget->update();
}

RoutersVehiclesDialog::~RoutersVehiclesDialog()
{
    // Destructor
}

void RoutersVehiclesDialog::loadCSVData(const QString& filePath, QTableWidget* tableWidget)
{
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        int row = 0;

        // Clear the existing table contents
        tableWidget->clear();
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            // Remove double quotes from the line
            line.remove("\"");

            QStringList rowData = line.split(",");

            if (tableWidget->columnCount() < rowData.size()) {
                // Set the column count to match the number of data columns
                tableWidget->setColumnCount(rowData.size());
            }

            tableWidget->insertRow(row); // Insert a new row before adding data

            for (int col = 0; col < rowData.size(); ++col)
            {
                QTableWidgetItem* item = new QTableWidgetItem(rowData[col]);
                tableWidget->setItem(row, col, item);
            }
            qDebug() << "Row " << row << " Data: " << rowData; // Debug: Output rowData for each row
            ++row;
        }

        file.close();
    }
}
