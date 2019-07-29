#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPoint first,secund;
    QImage* img = new QImage(400,400,QImage::Format_RGB32);
    void mousePressEvent(QMouseEvent *);

    bool one = false;

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *);

    void Line(int x1, int y1, int x2, int y2);
};

#endif // MAINWINDOW_H
