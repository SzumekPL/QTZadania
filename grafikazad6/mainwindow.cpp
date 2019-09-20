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

void MainWindow::clear()
{
    img->fill(QColor(255,255,255));
}

int maxValueY( QVector < QPoint > points )
{
    int max = 0;
    for(int i = 0; i < points.size(); ++i)
    {
        if(max < points[i].y())
        {
            max = points[i].y();
        }
    }
    return max;
}

int minValueY( QVector < QPoint > points )
{
    int min = points[0].y();
    for(int i = 1; i < points.size(); ++i)
    {
        if(min > points[i].y())
        {
            min = points[i].y();
        }
    }
    return min;
}

void MainWindow::fill(uchar r, uchar g, uchar b)
{
    int up = maxValueY(points);  //gora figury
    int down = minValueY(points);  // dol figury
    for (int y = down; y <= up; y++)
    {
        QVector <int> xValues;    // na ktorych iksach zaczac / przestac kolorowac
        for(int i = 0; i < points.size() - 1; ++i)
        {
            int j = i + 1; // j to numer kolejnego wierzcholka, poniewaz pi i pj tworza krawedz
            if (((y >= points[i].y()) && (y < points[j].y())) || ((y < points[i].y()) && (y >= points[j].y() ))) // sprawdzamy czy y przecina krawedz
                                                                                              // yi i yj nie moga byc rowne ze wzgledu na nierownosci
            {
                int x = int(points[i].x() + ((float((points[j].x() - points[i].x())) / (points[j].y() - points[i].y())) * (y - points[i].y())));
                // wyliczamy x'a na którym zaczyna się przeciecie
                xValues.push_back(x);
                //wrzucamy do tablicy
            }
        }

        // sprawdzenie dla ostatniego wierzchołka i pierwszego (ostatniej krawedzi)
        if (((y >= points[points.size() - 1].y()) && (y < points[0].y())) || ((y < points[points.size() - 1].y()) && (y >= points[0].y() )))
        {
            int x = int(points[points.size() - 1].x() + ((float((points[0].x() - points[points.size() - 1].x()))
                        / (points[0].y() - points[points.size() - 1].y())) * (y - points[points.size() - 1].y())));
            xValues.push_back(x);
        }

        // sortujemy tablice x'ów
        std::sort(xValues.begin(), xValues.end());

        // wykonujemy pętle po 2 ze względu na zasade parzystości
        for (int i = 0; i < xValues.size()-1; i+=2)
        {
            line(xValues[i], y, xValues[i + 1], y, r, g, b);
        }
    }
}

void MainWindow::draw()
{
    for(int i = 1; i < points.size(); ++i)
    {
        line(points[i-1].x(),points[i-1].y(),
             points[i].x()  ,points[i].y());
    }
    line(points[points.size()-1].x(),points[points.size()-1].y(),
         points[0].x()          ,points[0].y());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(points.empty())
    {
        points.push_back(QPoint(event->x(),event->y()));
    }
    else
    {
        points.push_back(QPoint(event->x(),event->y()));
        clear();
        draw();
    }
}

void MainWindow::line(int x1, int y1, int x2, int y2, uchar r, uchar g , uchar b)
{
    float t;
    int x, y;

    if (abs(x2 - x1) >= abs(y2 - y1) && x1 <= x2) // [-45, 45]
    {
        for (x = x1; x <= x2; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(round(y1 + double(t) * (y2 - y1)));
            img->setPixelColor(x, y, QColor(r,g,b));
        }
    }
    if (abs(x2 - x1) >= abs(y2 - y1) && x1 > x2) // [135, 225]
    {
        for (x = x2; x <= x1; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(round(y1 + double(t) * (y2 - y1)));
            img->setPixelColor(x, y, QColor(r,g,b));
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 > y2) // [45, 135]
    {
        for (y = y2; y <= y1; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            img->setPixelColor(x, y, QColor(r,g,b));
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 <= y2) // [225, 315]
    {
        for (y = y1; y <= y2; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            img->setPixelColor(x, y, QColor(r,g,b));
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

void MainWindow::on_pushButton_clicked()
{
    fill(100,255,78);
    draw();
}

void MainWindow::on_pushButton_2_clicked()
{
    clear();
    points.clear();
}
