#ifndef CRADLEPOINTROUTER_H
#define CRADLEPOINTROUTER_H
#include<QFile>
#include<QTextStream>
#include<QStringList>
#include<QMap>

#include<iostream>

class CradlePointRouter
{
public:
    CradlePointRouter();
    void setCradlePointCSV( const QString& file);
    QMap<QString,QString>getCradlePointCSV();

private:
    QMap<QString,QString>cradlePointCSV;
};

#endif // CRADLEPOINTROUTER_H
