#ifndef ROUTER_H
#define ROUTER_H
#include<QString>
#include<QVector>
#include<QMap>
#include<QFile>
#include<QTextStream>
#include<iostream>

class Router
{
public:
    virtual void setRouterFile(const QString & file);
    virtual void setRouter(QMap<QString,QString> &routerMap, const QString & file);
    virtual bool checkValue(const QMap<QString,QString> &routerMap,std::string value);
    //virtual QVector<QMap<QString, QString>> searchRows(const QMap<QString,QString> &routerMap,const QString& searchValue);
    virtual void searchRows(const QMap<QString,QString> &routerMap,const QString& searchValue);
    virtual QVector<QMap<QString,QString>> getRows();
    virtual QMap<QString,QString>getRouterCSV();

private:
    QVector<QMap<QString, QString>> matchingRows;
    QMap <QString,QString> router;
};

#endif // ROUTER_H
