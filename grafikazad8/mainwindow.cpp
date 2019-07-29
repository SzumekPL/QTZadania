#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->red->setMaximum(255);
    ui->green->setMaximum(255);
    ui->blue->setMaximum(255);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::RGBtoHSV(int red, int blue,int green, double valueH, double valueS, double valueV)
{
    double max, min;
    double delta;
    double r = red / 255.0;
    double g = green / 255.0;
    double b = blue / 255.0;
    max = qMax(qMax(r,g),b);
    min = qMin(qMin(r,g),b);
    valueV = max;
    delta = max - min;
    if (max != 0)
    {
        valueS = delta/max;
    }
    else
    {
        valueS = 0;
        valueH = -1;
        return;
    }

    if (max == r)
    {
        valueH = 60 * ((g - b) / delta);
    }
    else if (max == g)
    {
        valueH = 60 * (2 + ((b - r) / delta));
    }
    else if (max == b)
    {
        valueH = 60 * (4 + ((r - g) / delta));
    }
    if (valueH < 0)
    {
        valueH += 360;
    }
}

void MainWindow::on_pushButton_clicked()
{
    double h,s,v;
    RGBtoHSV(ui->red->value(),
             ui->green->value(),
             ui->blue->value(),
             h,s,v);
    QString string = "HSV: ";
    string += QString::number(h);
    string += " ";
    string += QString::number(s);
    string += " ";
    string += QString::number(v);
    string += " ";
    ui->label->setText(string);

}
