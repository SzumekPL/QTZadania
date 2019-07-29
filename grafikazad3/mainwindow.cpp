#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img->fill(QColor(255,255,255));
    ui->label->setPixmap(QPixmap::fromImage(*img, Qt::AutoColor));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(!one && !two)
    {
        first = QPoint(event->x(),event->y());
        one = true;
    }
    else if(!two && one)
    {
        secund = QPoint(event->x(),event->y());
        two = true;
    }
    else if (two && one)
    {
        Ellipse(first.x(),
                first.y(),
                pow((first.x()-secund.x())*(first.x()-secund.x())+(first.x()-secund.x())*(first.x()-secund.x()),0.5),
                pow((third.x()-secund.x())*(third.x()-secund.x())+(third.x()-secund.x())*(third.x()-secund.x()),0.5),
                1);
    }
}

void MainWindow::Line(int x1, int y1, int x2, int y2)
{
    float t;
    int x, y;

    if (abs(x2 - x1) >= abs(y2 - y1) && x1 <= x2) // [-45, 45]
    {
        for (x = x1; x <= x2; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(round(y1 + double(t) * (y2 - y1)));
            img->setPixelColor(x, y, QColor(0,0,0));
        }
    }
    if (abs(x2 - x1) >= abs(y2 - y1) && x1 > x2) // [135, 225]
    {
        for (x = x2; x <= x1; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(round(y1 + double(t) * (y2 - y1)));
            img->setPixelColor(x, y, QColor(0,0,0));
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 > y2) // [45, 135]
    {
        for (y = y2; y <= y1; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            img->setPixelColor(x, y, QColor(0,0,0));
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 <= y2) // [225, 315]
    {
        for (y = y1; y <= y2; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            img->setPixelColor(x, y, QColor(0,0,0));
        }
    }
    update();
}

void MainWindow::Ellipse(int x0, int y0, int R1, int R2, float Beta)
{
    int N = 60;
    float prev_x = 0, prev_y = 0;
    Beta = float(double(Beta) * M_PI / 180);
    for (int i = 0; i <= N; i++)
    {
        float Alpha = float(2 * M_PI * i / N);
        float x = float(R1 * cos(double(Alpha)));
        float y = float(R2 * sin(double(Alpha)));
        float x_beta = float(cos(double(Beta)) * double(x) + (-sin(double(Beta))) * double(y));
        float y_beta = float(sin(double(Beta)) * double(x) + cos(double(Beta)) * double(y));
        if (i > 0)
        {
            Line(int(prev_x) + x0, int(prev_y) + y0, int(x_beta) + x0, int(y_beta) + y0);
        }
        prev_x = x_beta;
        prev_y = y_beta;
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter pixel(this);

    pixel.drawImage(0,0,*img);

    ui->label->setPixmap(QPixmap::fromImage(*img, Qt::AutoColor));
   // imPrev = im;
   // update();
}
