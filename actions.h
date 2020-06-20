#ifndef ACTIONS_H
#define ACTIONS_H

# include <setup.h>
# include <ui_actions.h>
//# include <highlightdelegate.h>
class Actions: public QDialog, public Ui_Actions
{
    Q_OBJECT

public:
    Actions(QWidget *parent = nullptr);

};
#endif // MAINWINDOW_H
