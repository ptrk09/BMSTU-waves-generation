#ifndef DIALOG_NEW_WAVES_H
#define DIALOG_NEW_WAVES_H

#include <QDialog>

#include "handler.h"

namespace Ui {
class dialog_new_waves;
}

class dialog_new_waves : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_new_waves(QWidget *parent = nullptr);
    void update_list_waves(vector<QString> disc);
    ~dialog_new_waves();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    void delete_wave();
    shared_ptr<Handler> main_handler;
    Ui::dialog_new_waves *ui;
};

#endif // DIALOG_NEW_WAVES_H
