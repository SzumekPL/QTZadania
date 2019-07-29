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
    if(!one)
    {
        first = QPoint(event->x(),event->y());
        one = true;
    }
    else
    {
        secund = QPoint(event->x(),event->y());
        qDebug() << first.x() << first.y() << secund.x() << secund.y();
        Line(first.x(),first.y(),secund.x(),secund.y());
        one = false;
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

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter pixel(this);

    pixel.drawImage(0,0,*img);

    ui->label->setPixmap(QPixmap::fromImage(*img, Qt::AutoColor));
   // imPrev = im;
   // update();
}
