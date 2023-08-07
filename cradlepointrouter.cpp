#include "cradlepointrouter.h"

CradlePointRouter::CradlePointRouter()
{

}


void CradlePointRouter::setCradlePointCSV( const QString& filePath)
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
                cradlePointCSV.insert(headers[i], columns[i]);
            }
        }
    }//end while (!in.atEnd())


} //end void CradlePointRouter::setCradlePointCSV( const QString& filePath)


QMap<QString,QString>CradlePointRouter::getCradlePointCSV()
{
    return cradlePointCSV;
}

