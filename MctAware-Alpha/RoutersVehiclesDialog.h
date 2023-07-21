#ifndef ROUTERSVEHICLESDIALOG_H
#define ROUTERSVEHICLESDIALOG_H

#include <QDialog>

#include <QTabWidget>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>

    class RoutersVehiclesDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit RoutersVehiclesDialog(const QString& routerCSVPath, const QString& vehicleCSVPath, QWidget *parent = nullptr);
        ~RoutersVehiclesDialog();

    private:
        QTabWidget* tabWidget;
        QTableWidget* routerTableWidget;
        QTableWidget* vehicleTableWidget;
    };

#endif // ROUTERSVEHICLESDIALOG_H




