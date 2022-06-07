#include <QDesktopWidget>

#include "previewdialog.h"
#include "ui_previewdialog.h"

PreviewDialog::PreviewDialog(QWidget *parent, SszFile *ssz) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);

    QRect desktop = QApplication::desktop()->availableGeometry();
    int width, height;

    if (desktop.height() < 900)
    {
        width = 325;
        height = 650;
    }
    else
    {
        width = 419;
        height = 838;
    }

    setGeometry((desktop.width() / 2) - (width / 2), (desktop.height() / 2) - (height / 2), width, height);

    if (ssz->HasPreview())
    {
        size_t size;
        uint8_t *buf = ssz->GetPreview(&size);

        if (buf)
        {
            QPixmap pixmap;

            if (pixmap.loadFromData(buf, size))
            {
                ui->preview->setGeometry(0, 0, width, height);
                ui->preview->setPixmap(pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            }

            delete buf;
        }
    }

    setFixedSize(width, height);
}

PreviewDialog::~PreviewDialog()
{
   delete ui;
}
