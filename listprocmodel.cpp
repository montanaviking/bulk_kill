#include "listprocmodel.h"

ListProcModel::ListProcModel(QObject *parent): QStandardItemModel(parent), parentwidget(dynamic_cast<Actions *>(parent))
{
    //setRowCount(rows);
    //setColumnCount(2);
    clearall();
}


// add process to list
void ListProcModel::addprocs()
{   
    selectedprocesspartialname = parentwidget->processnamefilter->text();     // get partial name of selected processes from GUI as set by the user
    clearall();                                                       // remove all previous rows before rebuilding the table
    tobekilled.clear();                                                             // clear to be killed list
    auto rxselector = QRegExp("\\d[:]\\d\\d\\s");
    QStringList proclist = GetStdoutFromCommand("ps aux");          // run terminal command "ps aux" and obtain results in proclist
    if(!selectedprocesspartialname.trimmed().isEmpty())
    {
        for(auto x : proclist)
        {
            //auto idx=x.lastIndexOf(QRegExp("\\s\\d[:]\\d\\d\\s"));
            auto idx=x.lastIndexOf(rxselector);
            if(selectedprocesspartialname.length()>0 && x.length()>1 && idx!=-1 && !selectedprocesspartialname.trimmed().isEmpty())
            {
                auto procowner=QVariant(x.split(QRegExp("\\s+"),QString::SkipEmptyParts).at(0));                   // get process owner
                auto procid = QVariant(x.split(QRegExp("\\s+"),QString::SkipEmptyParts).at(1).toInt());         // get process ID number
                auto procname=QVariant(x.split(rxselector,QString::SkipEmptyParts).takeLast());                     // get process name
                //qDebug()<<"line 27 listprocmodel.cpp process name "<<x;
                if(procname.toString().contains(selectedprocesspartialname))
                {
                    appendrowproc(procid,procowner,procname);
                }
            }
        }
    }
    else        // add all processes to list if user hasn't selected any of them
    {
        for(auto x : proclist)
        {
            auto idx=x.lastIndexOf(QRegExp("\\s\\d[:]\\d\\d\\s"));
            if(x.length()>1 && idx!=-1)
            {
                auto procowner = QVariant(x.split(QRegExp("\\s+"),QString::SkipEmptyParts).at(0));
                auto procid = QVariant(x.split(QRegExp("\\s+"),QString::SkipEmptyParts).at(1).toInt());
                auto procname=QVariant(x.split(QRegExp("\\s\\d[:]\\d\\d\\s"),QString::SkipEmptyParts).at(1));
                //qDebug()<<"process name "<<procname;
                appendrowproc(procid,procowner,procname);
            }
        }
    }
    // consistency check
    if(rowCount()!=dataprocmodel.length())
    {
        std::cout<<"ERROR! from line 48 in listprocmodel.cpp: row count not consistent"<<std::endl;
        exit(1);
    }
    emit(updateviewwidth());        // update view's cell widths to accomodate new and/or changed data
    parentwidget->update();             // probably has no effect
}


void ListProcModel::killselectedprocs()
{
     qDebug()<<"from line 71 in listprocmodel.cpp killselectedproc()";
    for(auto procnumber : tobekilled)           // kill all processes having IDs specified in the QVector tobekilled
    {
        QString cmd = "kill "+QString::number(procnumber);
        const int max_buffer = 256;
        char buffer[max_buffer];
        FILE * stream=popen(cmd.toStdString().c_str(), "r");        // run shell command cmd and return results to buffer
        fgets(buffer, max_buffer, stream);
        pclose(stream);
        addprocs();                             // check processes and add to a new list those which are still running
    }
}



void ListProcModel::addproctobekilled(int row)
{
    tobekilled.append(data(index(row,0)).toInt());          // append process ID to be killed to kill list, QList<int> tobekilled
}

void ListProcModel::removeproctobekilled(int row)
{
    int idx = tobekilled.indexOf(data(index(row,0)).toInt());           // index of process ID from data
    tobekilled.removeAt(idx);          // append process ID to be killed to kill list, QList<int> tobekilled
}


QStringList ListProcModel::GetStdoutFromCommand(QString cmd)
{
    QString cmddata;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.toStdString().c_str(), "r");
    if (stream)
    {
    while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) cmddata.append(buffer);
    pclose(stream);
    }
    QStringList lines = cmddata.split("\n");
    return lines;
}

// kill all processes in table listing
//void ListProcModel::killallprocs()
//{
//    qDebug()<<"from line 114 in listprocmodel.cpp killallprocs() ";
//    QList<int>procnumlist;
//    QString selectedprocesspartialname = parentwidget->processnamefilter->text();     // get partial name of selected processes
//    if(!selectedprocesspartialname.trimmed().isEmpty())             // kill all processes ONLY if the user has specified a partial process name as a filter! If we didn't check this, we would kill all processes and crash the computer OS
//    {
//        for(int i=0;i<rowCount();i++)
//            tobekilled.append(data(index(i,1)).toInt());            // add all processes as specified by the user-set selectedprocesspartialname, to kill list
//        killallprocs();                                             // now kill all processes that were added to tobekilled
//    }
//}



QVariant ListProcModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        if(role==Qt::BackgroundRole)
        {
            auto rowu=unsigned(index.row());

            if(tobekilled.indexOf(data(this->index(rowu,0)).toInt())!=-1)         // is the process number on the to be killed list? in other words find the index of
                                                                                // the process number within the tobekilled QList. If the process number exists in
                                                                                // tobekilled, the found index will not be -1
            {
                return QVariant(QColor(Qt::red));               // mark processes to be killed in red background
            }
            else
            {
                return QVariant(QColor(Qt::white));             // not to be killed so use standard background coloring = white
            }
       }
       if(role==Qt::DisplayRole)                            // return data to view
       {
           return dataprocmodel.at(index.row()).at(index.column());     // return model data
       }
    }
    else return QVariant();                                 // invalid index, return empty QVariant
return QStandardItemModel::data(index,role);                // default standard behavior to update this model's view
}

void ListProcModel::appendrowproc(QVariant procid, QVariant powner, QVariant pname)
{
    setRowCount(rowCount()+1);              // increment row count
    dataprocmodel.append({procid,powner,pname});                                                               // append data to model
    if(dataprocmodel.length()!=rowCount())
    {
        std::cout<<"ERROR! line 136 in listprocmodel.cpp dataprocmodel.length() = "<<dataprocmodel.length()<<" rowCount = "<<rowCount()<<std::endl;
        exit(1);
    }
    int row=dataprocmodel.length()-1;                       // row number of the row being inserted
    int endcol=dataprocmodel.at(0).length();                // end column number which is the number of columns of the table
    emit(dataChanged(index(row,0),index(row,endcol)));      // inform view of new data
}


void ListProcModel::clearall()
{
    tobekilled.clear();
    dataprocmodel.clear();
    clear();
    setColumnCount(3);
    auto headers = QStringList(std::initializer_list<QString>{"Process ID number","Owner","Process Name"}); // set headers
    setHorizontalHeaderLabels(headers);
}

// clear all to-be-killed selections
void ListProcModel::clearkillselections()
{
    tobekilled.clear();
    emit(dataChanged(index(0,0),index(rowCount()-1,columnCount()-1)));
}


