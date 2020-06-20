#ifndef HIGHLIGHTDELEGATE_H
#define HIGHLIGHTDELEGATE_H

#include <setup.h>
#include <highlightfoundproc.h>

class HighLightDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    HighLightDelegate(QObject * parent=nullptr);
//    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void drawDisplay();
    //mutable HighlightFoundProc *highlighter;
//public slots:
//    void highlightprocname();
};

#endif // HIGHLIGHTDELEGATE_H
