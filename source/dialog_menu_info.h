#ifndef DIALOG_MENU_INFO_H
#define DIALOG_MENU_INFO_H

#include <QDialog>

namespace Ui {
class Dialog_menu_info;
}

class Dialog_menu_info : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_menu_info(QWidget *parent = nullptr);
    ~Dialog_menu_info();

private slots:

private:
    Ui::Dialog_menu_info *ui;
};

#endif // DIALOG_MENU_INFO_H
