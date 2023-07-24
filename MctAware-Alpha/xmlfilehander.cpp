#include "xmlfilehander.h"


//Default Constructor: Sets all private data members to a default value
XmlFileHander::XmlFileHander()
{
    xmlFileDialog = new  QFileDialog();
    directory = QDir::homePath(); //sets the default directory
    xmlFile  = QString::Null(); //set this to null for now
    QXmlStreamAttributes attributes;

}


//set Directory sets the directory
void XmlFileHander::setDirectory(QString dir)
{
    this->directory = dir; //set a path to the directory
}


//setXmlFile sets the XML file
void XmlFileHander::setXmlFile(QString xmlFileValue)
{
    QFile fileName(xmlFileValue); // convert to a file
    if(!fileName.open(QIODevice::ReadOnly | QIODevice::Text)) //check if we can open it and read it
    {
        QMessageBox::critical(nullptr,"ERROR","Could Not Open XML File",QMessageBox::Ok); // if not give this error
        QString file =
            QFileDialog::getOpenFileName(nullptr, "Open config xml ", QString(), "XML Files (*.xml)"); //open a dialog box so person can find it
        this->setXmlFile(file); // set the file name
    }
    else
    {
        xmlFile = xmlFileValue;
    }
}


//setTagName gets all the tag names
  void XmlFileHander::setTagNames(QString filePath)
{

    QFile file(filePath);
    QXmlStreamReader xmlReader(&file);

    //QStringList tagNames; // Store all the tag names

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement) {
            QString elementName = xmlReader.name().toString();
            tagNames.append(elementName); // Add the tag name to the list
        }
    }

    file.close();

}

/*void XmlFileHander::setAttributesFromTag(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Handle error if the file couldn't be opened
        QMessageBox::critical(nullptr, "ERROR", "Could Not Open XML File", QMessageBox::Ok);
        return;
    }

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError())
    {
        if (xml.isStartElement())
        {
            QString tagName = xml.name().toString();
            if (tagNames.contains(tagName))
            {
                this->attributes = xml.attributes();
                if (!attributes.isEmpty())
                {
                    qDebug() << "Tag name:" << tagName;
                    qDebug() << "Attributes:";
                    for (const QXmlStreamAttribute& attr : attributes)
                    {
                        qDebug() << attr.name().toString() << "=" << attr.value().toString();
                    }
                }
            }
        }

        xml.readNext();
    }

    if (xml.hasError())
    {
        // Handle XML parsing error
        QMessageBox::critical(nullptr, "ERROR", "Could Not Parse XML File", QMessageBox::Ok);
    }

    file.close();
}
*/


std::string XmlFileHander::getDirectory()
{
    return this->directory.toStdString();
}


std::string XmlFileHander::getXmlFile()
{
    return this->xmlFile.toStdString();
}


std::vector<std::string> XmlFileHander::getTagNames()
{
    std::vector<std::string> tags;
    for (const QString& tagName : tagNames)
    {
        tags.push_back(tagName.toStdString());
    }

    return tags;
}
