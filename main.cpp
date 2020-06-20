#include "actions.h"

#include <QApplication>

#include <streambuf>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <QString>
#include <QList>

using namespace std;


int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    Actions mw(nullptr);
    mw.show();
   return app.exec();
}
