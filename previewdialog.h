#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>

#include "SszFile.h"

namespace Ui {
class PreviewDialog;
}

class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewDialog(QWidget *parent, SszFile *ssz);
    ~PreviewDialog();

private:
    Ui::PreviewDialog *ui;    
};

#endif // PREVIEWDIALOG_H
