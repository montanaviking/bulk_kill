#include "procview.h"

ProcessView::ProcessView(QWidget * parent): QTableView(parent)
{
    setMouseTracking(true);     // needed to catch mouse moves
    resizeColumnsToContents();
    resizeRowsToContents();
    verticalHeader()->hide();                       // hide left side table headers
    setSortingEnabled(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);     // set whole table as read-only
}

void ProcessView::mousePressEvent(QMouseEvent *me)
{
    QModelIndex posindex = indexAt(me->pos());     // get model cell index at mouse position to obtain selected cell
    int row = posindex.row();
    if(model()==nullptr) std::cout<<"ERROR! no model set for view"<<std::endl;   // catch lack of model for this view. This should not occur and is for debug

    if(me->button()==Qt::LeftButton)
    {
        if (row>-1 && row<listprocmodel->rowCount())
        {
            listprocmodel->addproctobekilled(row);                          // add the selected process number to those to be killed
            emit(dataChanged(listprocmodel->index(row,0),listprocmodel->index(row,listprocmodel->columnCount()-1)));
        }
        else
        {
            QTableView::mousePressEvent(me);                            // otherwise pass mouse event to base class
        }
    }
    else if(me->button()==Qt::RightButton)          // then undo this selection
    {
        if (row>-1 && row<listprocmodel->rowCount())
        {
            listprocmodel->removeproctobekilled(row);                          // remove the selected process number to those to be killed
            emit(dataChanged(listprocmodel->index(row,0),listprocmodel->index(row,listprocmodel->columnCount()-1)));
        }
        else
        {
            QTableView::mousePressEvent(me);                            // otherwise pass mouse event to base class
        }
    }
    else
    {
        QTableView::mousePressEvent(me);                            // otherwise pass mouse event to base class
    }
}

void ProcessView::setModel(QAbstractItemModel *setmodel)
{
    QTableView::setModel(setmodel);            //default setting of model
    listprocmodel =dynamic_cast<ListProcModel *> (model());         // set alias of the view's model
    connect(listprocmodel,SIGNAL(updateviewwidth()),this,SLOT(updatecolumnwidth()));
}

void ProcessView::updatecolumnwidth()                   // slot to resize column widths. Typically called by the model when data changes
{
    resizeRowsToContents();
    resizeColumnsToContents();
}
