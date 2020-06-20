#include "actions.h"
#include "listprocmodel.h"
#include "procview.h"
#include "highlightdelegate.h"


Actions::Actions(QWidget *parent): QDialog(parent)
{
    setupUi(this);
    setUpdatesEnabled(true);
    //QString partialprocessname = selectedprocess->text();       // get partial process name
    auto procmodel = new ListProcModel(this);          // get process table model
    auto procview = new ProcessView(this);                  // get process table view
    auto highlightdelegate=new HighLightDelegate(this);
    procview->setItemDelegate(highlightdelegate);
    procview->setModel(dynamic_cast<ListProcModel *>(procmodel));
    procview->horizontalHeader()->setStretchLastSection(true);
    proctablelayout->addWidget(procview);

    killselectedbutton->blockSignals(true);
    processnamefilter->blockSignals(true);
    clearbutton->blockSignals(true);
    connect(processnamefilter,SIGNAL(editingFinished()),procmodel,SLOT(addprocs()));        // read processes from system upon entry of the process name filter
    connect(clearbutton,SIGNAL(clicked()),procmodel,SLOT(clearkillselections()));
    connect(killselectedbutton,SIGNAL(clicked()),procmodel,SLOT(killselectedprocs()));
    killselectedbutton->blockSignals(false);
    processnamefilter->blockSignals(false);
    clearbutton->blockSignals(false);
    //HighlightFoundProc *highlightproc=new HighlightFoundProc(processnamefilter->document());
}

