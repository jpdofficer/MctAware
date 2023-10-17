#include "router.h"

//setRouterFile sets the location of the router.csv
void Router::setRouterFile(const QString & filePath){
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Failed to open file:" << file.errorString().toStdString();
        return;
    }//end if (!file.open(QIODevice::ReadOnly | QIODevice::Text))

    QTextStream in(&file);
    QStringList headers;
    bool isFirstLine = true;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList columns = line.split(",");

        if (isFirstLine) {
            headers = columns;
            isFirstLine = false;
        } else {
            for (int i = 0; i < columns.size() && i < headers.size(); ++i) {
                router.insert(headers[i], columns[i]);
            }
        }
    }//end while (!in.atEnd())


} //end void CradlePointRouter::setCradlePointCSV( const QString& filePath)



void Router::setRouter( QMap<QString,QString>& router, const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Failed to open file:" << file.errorString().toStdString();
        return;
    }//end if (!file.open(QIODevice::ReadOnly | QIODevice::Text))

    QTextStream in(&file);
    QStringList headers;
    bool isFirstLine = true;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList columns = line.split(",");

        if (isFirstLine) {
            headers = columns;
            isFirstLine = false;
        } else {
            for (int i = 0; i < columns.size() && i < headers.size(); ++i) {
                router.insert(headers[i], columns[i]);
            }
        }
    }//end while (!in.atEnd())


} //end void CradlePointRouter::setCradlePointCSV( const QString& filePath)


QMap<QString,QString>Router::getRouterCSV()
{
    return router;
}


//returns a value to the called from the provided key
bool Router::checkValue(const QMap<QString,QString> & router,std::string stdStringValue)
{
    //Check if the keyExist
    if(router.contains(QString::fromStdString(stdStringValue)))
    {

        return true;

    }//end if(cradlePointCSV.contains(QString::fromStdString(stdStringKey)));
    else
    {
        return false;
    }//end else

    }
void Router::searchRows(const QMap<QString,QString> & router, const QString& searchValue)
{
    matchingRows.clear();

    for (auto it = router.begin(); it != router.end(); ++it) {
        const QString& key = it.key();
        const QString& value = it.value();

        if (value == searchValue) {
            matchingRows.append(QMap<QString, QString>{{key, value}});
        }
    }


}

QVector<QMap<QString,QString>> Router::getRows()
{
    return matchingRows;
}
