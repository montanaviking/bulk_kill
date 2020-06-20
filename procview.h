#ifndef PROCVIEW_H
#define PROCVIEW_H

#include <setup.h>
#include <listprocmodel.h>

class ProcessView: public QTableView
{
    Q_OBJECT
public:
    ProcessView(QWidget *parent=nullptr);
    void setModel(QAbstractItemModel *setmodel) override;
private:
    void mousePressEvent(QMouseEvent *me) override;
    ListProcModel *listprocmodel=nullptr;           // alias of model
public slots:
    void updatecolumnwidth();                       // update column width, allows model to update the column width to fit data size
};

#endif // PROCVIEW_H
