#ifndef LISTPROCMODEL_H
#define LISTPROCMODEL_H
#include <setup.h>
#include <actions.h>            // parent class definitions

class ListProcModel: public QStandardItemModel
{
    Q_OBJECT
public:
    ListProcModel(QObject *parent=nullptr);
    void addproctobekilled(int row);                     // add process to be killed
    void removeproctobekilled(int row);                     // remove the process to be killed identified by its process ID number
    QString selectedprocesspartialname="";
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QList<int> tobekilled;           // process numbers of processes to be killed
private:
    Actions * parentwidget = nullptr;                   // parent alias
    QStringList GetStdoutFromCommand(QString cmd);
    //QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QList<QList<QVariant>> dataprocmodel;     // model's data
    void clearall();                // clear all model data and set number of rows to zero
    void appendrowproc(QVariant procid, QVariant powner, QVariant pname);
public slots:
    void killselectedprocs();            // kill processes specified by tobekilled
    //void killallprocs();                // kill all processes listed, unless process selection is empty (no partial process name specified)
    void addprocs();
    void clearkillselections();         // clears all to be killed selections
signals:
    void updateviewwidth();
};

#endif // LISTPROCMODEL_H
