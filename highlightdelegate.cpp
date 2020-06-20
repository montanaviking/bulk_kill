#include "highlightdelegate.h"
HighLightDelegate::HighLightDelegate(QObject *parent): QStyledItemDelegate(parent)
{
    std::cout<<"line 4 in highlightdelegate.cpp"<<std::endl;
}
//QWidget* HighLightDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    auto *editor=new QTextEdit(index.data().toString(),parent);
//    QTextEdit *ed = dynamic_cast<QTextEdit *>(editor);
//    highlighter=new HighlightFoundProc(ed->document());
//    std::cout<<"line 11 in highlightdelegate.cpp"<<std::endl;
//    return editor;
//}

//void HighLightDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    auto celltext = dynamic_cast<QTextEdit *>(editor);
//    celltext->setText(index.model()->data(index,Qt::DisplayRole).toString());
//    highlighter->rehighlight();
//    std::cout<<"line 20 in highlightdelegate.cpp"<<std::endl;
//}
//void HighLightDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{
//    QTextEdit *ed = dynamic_cast<QTextEdit *>(editor);
//    model->setData(index,QVariant::fromValue(ed->toPlainText()));
//    std::cout<<"line 26 in highlightdelegate.cpp"<<std::endl;
//}

void HighLightDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==2)
    {
        const ListProcModel * model=dynamic_cast<const ListProcModel *>(index.model());
        auto proctext = QTextDocument(index.data().toString());     // proctext is the process name. We wish to highlight the search term(s)
        HighlightFoundProc * highlt = new HighlightFoundProc(&proctext,model);      // set up highlighter on process ID text
        painter->save();
        //auto background=QBrush(QColor(Qt::red),Qt::SolidPattern);
        auto rowtokill = unsigned(index.row());
        //auto proctokill=index.data().toInt();
        auto proctokill=model->index(index.row(),0).data().toInt();     // process ID to kill
        auto tobekilledindex=model->tobekilled.indexOf(proctokill);
        if(tobekilledindex!=-1)         // is the process number on the to be killed list? in other words find the index of
                                                                            // the process number within the tobekilled QList. If the process number exists in
                                                                            // tobekilled, the found index will not be -1
        {
           auto background=QBrush(QColor(Qt::red),Qt::SolidPattern);               // mark processes to be killed in red background
           std::cout<<"from line 52 in highlightdelegate.cpp rowtokill "<<rowtokill<<" tobekilledindex = "<<tobekilledindex<<" proctokill = "<<proctokill<<std::endl;
           painter->setBrush(background);
           painter->drawRect(option.rect);
        }

        highlt->rehighlight();                              // highlight text in proctest QTextDocument
        painter->translate(option.rect.x(),option.rect.y());
        proctext.drawContents(painter);
        painter->restore();
        //delete highlt;
    }
    else QStyledItemDelegate::paint(painter, option, index);
}
