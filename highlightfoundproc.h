#ifndef HIGHLIGHTFOUNDPROC_H
#define HIGHLIGHTFOUNDPROC_H
#include <setup.h>
#include <listprocmodel.h>

class HighlightFoundProc : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    HighlightFoundProc(QTextDocument *parent=nullptr,const ListProcModel *model=nullptr);
    void highlightBlock(const QString &text) override;
private:
    //QString texttofind={""};                // text to find and highlight in procname results
    const ListProcModel * procmodel=nullptr;
//public slots:
//    void selectedprocesspartialname_changed(QString pprocname);             // slot for changing name of process
};

#endif // HIGHLIGHTFOUNDPROC_H
