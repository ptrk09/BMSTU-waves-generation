#include "dialog_menu_info.h"
#include "ui_dialog_menu_info.h"

Dialog_menu_info::Dialog_menu_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_menu_info)
{
    ui->setupUi(this);
}

Dialog_menu_info::~Dialog_menu_info() {
    delete ui;
}
