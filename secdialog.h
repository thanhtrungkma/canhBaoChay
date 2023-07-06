#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include "thirddialog.h"

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_dht_clicked();

private:
    Ui::SecDialog *ui;
    ThirdDialog *thirdDialog;
};

#endif // SECDIALOG_H
