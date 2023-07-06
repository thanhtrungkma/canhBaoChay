#include "thirddialog.h"
#include "ui_thirddialog.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

#define MAXTIMINGS	85
#define DHTPIN		7
#define DHTPIN2		9
#define FLAME_PIN 20
#define FLAME_PIN2 16

int		dht11_dat[5] = { 0, 0, 0, 0, 0 };
double	temp;
double	humidity;

void ThirdDialog::read() {
        wiringPiSetupGpio();
        pinMode(FLAME_PIN, INPUT);
            if(digitalRead(FLAME_PIN) == LOW) {
                QMessageBox::warning(this,"Warning", "Fire detected 1");
                qDebug()<<"chay 1\n";
            }

}

void ThirdDialog::read2() {
        wiringPiSetupGpio();
        pinMode(FLAME_PIN2, INPUT);
            if(digitalRead(FLAME_PIN2) == LOW) {
                QMessageBox::warning(this,"Warning", "Fire detected 2");
                //qDebug()<<"chay 2\n";
            }

}


int read_dht11_dat()
{
    uint8_t		laststate = HIGH;
    uint8_t		counter = 0;
    uint8_t		j = 0, i;

    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);
    digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40);
    pinMode(DHTPIN, INPUT);

    for (i = 0; i < MAXTIMINGS; i++)
    {
        counter = 0;
        while (digitalRead(DHTPIN) == laststate)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
                break;
        }
        laststate = digitalRead(DHTPIN);

        if (counter == 255)
            break;

        if ((i >= 4) && (i % 2 == 0))
        {
            dht11_dat[j / 8] <<= 1;
            if (counter > 64)
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)))
    {
        temp = dht11_dat[2] + (dht11_dat[3] / 10);
        humidity = dht11_dat[0] + (dht11_dat[1] / 10);
        return (1);
    }
    else
        return (0);
}

int read_dht11_dat2()
{
    uint8_t		laststate = HIGH;
    uint8_t		counter = 0;
    uint8_t		j = 0, i;

    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    pinMode(DHTPIN2, OUTPUT);
    digitalWrite(DHTPIN2, LOW);
    delay(18);
    digitalWrite(DHTPIN2, HIGH);
    delayMicroseconds(40);
    pinMode(DHTPIN2, INPUT);

    for (i = 0; i < MAXTIMINGS; i++)
    {
        counter = 0;
        while (digitalRead(DHTPIN2) == laststate)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
                break;
        }
        laststate = digitalRead(DHTPIN2);

        if (counter == 255)
            break;

        if ((i >= 4) && (i % 2 == 0))
        {
            dht11_dat[j / 8] <<= 1;
            if (counter > 64)
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)))
    {
        temp = dht11_dat[2] + (dht11_dat[3] / 10);
        humidity = dht11_dat[0] + (dht11_dat[1] / 10);
        return (1);
    }
    else
        return (0);
}


ThirdDialog::ThirdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdDialog)
{
    ui->setupUi(this);
    /*
        int activity = 0;
        while(activity != 1) {
            activity = read();
            if(activity == 1) {
                QMessageBox::warning(this,"Warning", "Fire detected 1");
            }
        }*/
    //QTimer::singleShot(0, this, SLOT(read));
    //QTimer::singleShot(0, this, SLOT(read2));
    /*thread1 = QThread::create([]{
        wiringPiSetupGpio();
        pinMode(FLAME_PIN, INPUT);
        while(1){
            if(digitalRead(FLAME_PIN) == LOW) {
                //QMessageBox::warning("Warning", "Fire detected 1");
                qDebug()<<"chay 1\n";
            }
        }
    });
    thread1->start();*/
    timer1 = new QTimer(this);
    QObject::connect(timer1, SIGNAL(timeout()), this, SLOT(read()));
    timer1->start(1000); //time specified in ms

    timer2 = new QTimer(this);
    QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(read2()));
    timer2->start(1000); //time specified in ms
}

ThirdDialog::~ThirdDialog()
{
    delete ui;
}

void ThirdDialog::readDHT1() {
    int ret = 0;

    if (wiringPiSetup() == -1)
        exit(1);
    if(ret == 0)
    {
        ret = read_dht11_dat();
        QString valueAsString = QString::number(temp);
        QMessageBox::information(this, "Temp", "Room 1: " + valueAsString + " C");
        delay(100);
    }
}

void ThirdDialog::on_pushButton_Temp_clicked()
{
        //timer2 = new QTimer(this);

        //connect(timer2, SIGNAL(timeout()), this, SLOT(readDHT1()));
        //timer2->start(1000);
}

void ThirdDialog::on_pushButton_back_clicked()
{

    hide();
    parentWidget()->show();
}

void ThirdDialog::on_pushButton_Temp2_clicked()
{
    int ret = 0;

        if (wiringPiSetup() == -1)
            exit(1);
        if(ret == 0)
        {
            ret = read_dht11_dat2();
            QString valueAsString = QString::number(temp);
            QMessageBox::information(this, "Temp", "Room 2: " + valueAsString + " C");
            delay(100);
        }
}
