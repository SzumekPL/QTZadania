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
        Circle(first.x(),
               first.y(),
               pow(( first.x() - secund.x() ) * ( first.x() - secund.x() )+
                   ( first.y() - secund.y() ) * ( first.y() - secund.y() ),
                   0.5));
        one = false;
    }
}

void MainWindow::Circle(int x0, int y0, int R)
{
    float a = float(R / sqrt(2));
    for(int x = 0; x <= a; x++)
    {
        int y = int(sqrt(R*R - x*x));
        img->setPixelColor(x + x0, y + y0, QColor(0,0,0));
        img->setPixelColor(y + x0, x + y0, QColor(0,0,0));
        img->setPixelColor(-x + x0, y + y0, QColor(0,0,0));
        img->setPixelColor(-y + x0, x + y0, QColor(0,0,0));
        img->setPixelColor(-x + x0, -y + y0, QColor(0,0,0));
        img->setPixelColor(-y + x0, -x + y0, QColor(0,0,0));
        img->setPixelColor(x + x0, -y + y0, QColor(0,0,0));
        img->setPixelColor(y + x0, -x + y0, QColor(0,0,0));
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
