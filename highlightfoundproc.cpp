#include "highlightfoundproc.h"

HighlightFoundProc::HighlightFoundProc(QTextDocument *parent,const ListProcModel *model):QSyntaxHighlighter(parent), procmodel(model)
{}
void HighlightFoundProc::highlightBlock(const QString &procparameter)       //procparameter is the process name or owner depending on use
{
    int len = procparameter.size();
    int foundpos=-1;
    int nextpos=0;
    auto texttofind=procmodel->selectedprocesspartialname;
    if(texttofind.size()==0) return;
    do
    {
        foundpos=procparameter.indexOf(texttofind,nextpos,Qt::CaseInsensitive);     // find first searched substring in the process name or process owner
        if(foundpos>=0 && texttofind.size()>0 && nextpos<len)        // found instance of texttofind in procparameter so need to highlight
        {
            nextpos=foundpos+texttofind.size()-1;           // get next position to search for text
            if(nextpos<len)
                {
                setFormat(foundpos,texttofind.size(),QColor(Qt::green));
                //std::cout<<"from line 21 highlightfoundproc.cpp texttofind ="<<texttofind.toStdString()<<" size= "<<texttofind.size()<<" foundpos = "<<foundpos<<" nextpos-1 "<<nextpos-1<<" procparameter = "<<procparameter.toStdString()<<std::endl;
                }
            }
    }
    while(foundpos!=-1 && nextpos<len);
}
