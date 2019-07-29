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
    points.push_back(event->pos());
    if(points.size() > 3)
    {
        SplineCurve(points[0], points[1], points[2], points[3]);
        points.clear();
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

void MainWindow::SplineCurve(QPoint p0, QPoint p1, QPoint p2, QPoint p3)
{
    int x, y;
    int prev_x = 0, prev_y = 0;
    int n = 20;
    for (int t = 0; t <= n; t++)
    {
        float T = float(t)/n;
        x = int(float(1)/6 * (-(T*T*T) + 3*T*T - 3*T + 1) * p0.x()
                + float(1)/6 * (3*T*T*T - 6*T*T + 4) * p1.x()
                + float(1)/6 * (-3*T*T*T + 3*T*T + 3*T + 1) * p2.x()
                + float(1)/6 * T*T*T * p3.x());
        y = int(float(1)/6 * (-(T*T*T) + 3*T*T - 3*T + 1) * p0.y()
                + float(1)/6 * (3*T*T*T - 6*T*T + 4) * p1.y()
                + float(1)/6 * (-3*T*T*T + 3*T*T + 3*T + 1) * p2.y()
                + float(1)/6 * T*T*T * p3.y());
        if (t > 0)
        {
            Line(prev_x, prev_y, x, y);
        }
        prev_x = x;
        prev_y = y;
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
