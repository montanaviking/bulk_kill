#include "actions.h"

#include <QApplication>

#include <streambuf>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <QString>
#include <QList>

using namespace std;
QStringList GetStdoutFromCommand(QString cmd)
{
    QString data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.toStdString().c_str(), "r");
    if (stream)
    {
    while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }
    QStringList lines = data.split("\n");
    return lines;
}

// kill process using process ID = pnumber
// return shell message after kill
QString killprocess(int pnumber)
{
    QString cmd="kill ";
    cmd+=" "+QString::number(pnumber);
    QStringList results;
    const int max_buffer = 256;
    char buffer[max_buffer];

    FILE * stream=popen(cmd.toStdString().c_str(), "r");        // run shell command cmd and return results to buffer
    if (fgets(buffer, max_buffer, stream) != NULL)
        return(QString(buffer));
    else return(QString(""));
}


using namespace std;
//int main(int argc, char *argv[])

int main()
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//   return a.exec();

    QStringList proclist = GetStdoutFromCommand("ps aux");

    for(auto x : proclist)
    {
    if(x.split(QRegExp("\\s+"),QString::SkipEmptyParts).length()>2)
        {
        auto procid = x.split(QRegExp("\\s+"),QString::SkipEmptyParts).at(1).toInt();
        auto procowner = x.split(QRegExp("\\s+"),QString::SkipEmptyParts).at(0);
        if(x.contains("eesof"))
            {
            cout <<" proc owner "<<procowner.toStdString()<< " proc ID "<<procid<< endl;
            }
        }
    }

    return 0;


}
