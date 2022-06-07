#ifndef INSTALLDIALOG_H
#define INSTALLDIALOG_H

#include <QDialog>

#include "SszFile.h"

namespace Ui {
class InstallDialog;
}

enum class InstallType
{
    INSTALL,
    UPDATE,
    OVERWRITE,
};

class InstallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InstallDialog(QWidget *parent, SszFile *ssz, InstallType type);
    ~InstallDialog();

private slots:
    void on_yesButton_clicked();

    void on_noButton_clicked();

    void on_previewButton_clicked();

private:
    Ui::InstallDialog *ui;

    SszFile *ssz;
    InstallType type;
};

#endif // INSTALLDIALOG_H
