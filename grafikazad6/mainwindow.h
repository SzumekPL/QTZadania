#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPoint clickPoint;
    QImage* img = new QImage(400,400,QImage::Format_RGB32);
    void mousePressEvent(QMouseEvent *);

    QVector <QPoint> points;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *);

    void line(int x1, int y1, int x2, int y2, uchar r = 0, uchar g = 0, uchar b = 0);
    void clear();
    void draw();
    void fill(uchar r, uchar g, uchar b);
};

#endif // MAINWINDOW_H
