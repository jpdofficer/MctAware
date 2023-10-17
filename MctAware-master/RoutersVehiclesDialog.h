#ifndef ROUTERSVEHICLESDIALOG_H
#define ROUTERSVEHICLESDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QFile>
#include<QTextStream>
#include<QMessageBox>

class RoutersVehiclesDialog : public QDialog
{
    Q_OBJECT

public:
    RoutersVehiclesDialog();
    explicit RoutersVehiclesDialog(const QString& routerCSVPath, const QString& vehicleCSVPath, QWidget* parent = nullptr);
    void setRouterCSVPath(QString &csvPath);
    void setVehicleCSVPath(QString &vehiclePath);

    QString getRouterCSV();
    QString getVehicleCSVPath();
    ~RoutersVehiclesDialog();

private:
    QTabWidget* tabWidget;
    QTableWidget* routerTableWidget;
    QTableWidget* vehicleTableWidget;

    void loadCSVData(const QString& filePath, QTableWidget* tableWidget);
};

#endif // ROUTERSVEHICLESDIALOG_H
