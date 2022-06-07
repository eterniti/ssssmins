#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

#include "SlotsFile.h"

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent, SlotsFile *slf);
    ~SelectDialog();

private slots:
    void onSlotButtonClicked();

    void on_cancelButton_clicked();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
