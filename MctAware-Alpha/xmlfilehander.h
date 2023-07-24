#ifndef XMLFILEHANDER_H
#define XMLFILEHANDER_H

#include<QDir>
#include<QFile>
#include<QMessageBox>
#include<QFileDialog>
#include<QXmlStreamReader>


class XmlFileHander
{
public:
    XmlFileHander();
    void setDirectory(QString dirPath); //sets the directory path
    void setXmlFile(QString filePath); //sets the file path.
    void setTagNames(QString filePath); //sets the QStringList that contains all tag attributes
    void setAttributesFromTag(const QString &filePath);


    std::string getDirectory(); //returns the directory path
    std::string getXmlFile(); //return the file path
    std::vector<std::string> getTagNames(); //returns the list back to the client

private:
    QStringList tagNames;
    QStringList attributes;
    QString directory;
    QString xmlFile;
    QFileDialog *xmlFileDialog;
};

#endif // XMLFILEHANDER_H
