#include <QDesktopWidget>

#include "selectdialog.h"
#include "ui_selectdialog.h"

// DELETE THIS unnecesary import
#include <QMessageBox>

SelectDialog::SelectDialog(QWidget *parent, SlotsFile *slf) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);    

    QRect desktop = QApplication::desktop()->availableGeometry();

    // Little easter egg
    if (Utils::RandomInt(0, 5) == 3)
    {
        QIcon icon;

        icon.addPixmap(QPixmap(":/images/icons59/1010_0317.png"), QIcon::Normal);
        icon.addPixmap(QPixmap(":/images/icons59 disabled/1010_0317.png"), QIcon::Disabled);
        ui->slb_67->setIcon(icon);
    }

    QRegExp exp("slb_*");
    QList <QPushButton *> list = findChildren<QPushButton *>(exp);

    for (QPushButton *b : list)
    {        
        int index = b->objectName().mid(4).toInt();

        if (desktop.width() >= 1600)
        {
            QSize size;
            int row, col;

            if (index < 25)
            {
                row = 0, col = index;
            }
            else if (index < 50)
            {
                row = 1, col = index-25;
            }
            else
            {
                row = 2, col = index-50;
            }

            size.setHeight(59);
            size.setWidth(59);
            b->setIconSize(size);
            b->setGeometry(b->x()+(col*19), b->y()+(row*19), 59, 59);
        }

        if (!slf->HasFreeSubSlot(index))
        {
            b->setEnabled(false);
        }

        connect(b, SIGNAL(clicked()), this, SLOT(onSlotButtonClicked()));
    }

    if (desktop.width() >= 1600)
    {
        int w = width() + 25*19;
        int h = height() + 3*19;

        setGeometry((desktop.width() / 2) - (w / 2) , (desktop.height() / 2) - (h / 2), w, h);
        ui->cancelButton->setGeometry(ui->cancelButton->x() + ((25*19) / 2), ui->cancelButton->y() + 3*19, ui->cancelButton->width(), ui->cancelButton->height());
    }

    setFixedSize(width(), height());
}

void SelectDialog::onSlotButtonClicked()
{
    QPushButton *button = (QPushButton *)sender();
    int index = button->objectName().mid(4).toInt();

    done(index+0x100);
}

void SelectDialog::on_cancelButton_clicked()
{
    done(0);
}

SelectDialog::~SelectDialog()
{
    delete ui;
}
