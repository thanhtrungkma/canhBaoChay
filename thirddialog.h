#ifndef THIRDDIALOG_H
#define THIRDDIALOG_H

#include <QDialog>


namespace Ui {
class ThirdDialog;
}

class ThirdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThirdDialog(QWidget *parent = nullptr);
    ~ThirdDialog();
    //PrintMsg *pm;
private slots:
    void on_pushButton_Temp_clicked();
    void read();
    void read2();
    void on_pushButton_back_clicked();
    void readDHT1();
//public slots:
    //void dislayMsg(int);
    void on_pushButton_Temp2_clicked();

private:
    Ui::ThirdDialog *ui;
     QTimer *timer1, *timer2, *timer3;
};

extern int		dht11_dat[5];
extern double	temp;
extern double	humidity;

#endif // THIRDDIALOG_H
