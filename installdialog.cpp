#include "installdialog.h"
#include "ui_installdialog.h"

#include "previewdialog.h"

InstallDialog::InstallDialog(QWidget *parent, SszFile *ssz, InstallType type) :
    QDialog(parent),
    ui(new Ui::InstallDialog)
{
    ui->setupUi(this);

    this->ssz = ssz;
    this->type = type;

    setFixedSize(width(), height());

    QString text;

    if (type == InstallType::INSTALL)
    {
       text = "Do you want to install the following mod?\n\n";
       ui->yesButton->setDefault(true);
    }
    else if (type == InstallType::UPDATE)
    {
        text = "Do you want to update the following mod?\n\n";
        ui->yesButton->setDefault(true);
        setWindowTitle("Update mod?");
    }
    else
    {
        text = "This mod is already installed. Do you want to reinstall it?\n\n";
        ui->noButton->setDefault(true);
        setWindowTitle("Reinstall mod?");
    }

    if (!ssz->HasPreview())
    {
        ui->previewButton->setEnabled(false);
    }

    text += "Mod name: " + QString::fromStdString(ssz->GetModName()) + "\n\n";
    text += "Mod author: " + QString::fromStdString(ssz->GetModAuthor());

    ui->label->setText(text);
}

InstallDialog::~InstallDialog()
{
    delete ui;
}

void InstallDialog::on_yesButton_clicked()
{
    done(1);
}

void InstallDialog::on_noButton_clicked()
{
    done(0);
}

void InstallDialog::on_previewButton_clicked()
{
    PreviewDialog dialog(this, ssz);

    dialog.exec();
}
