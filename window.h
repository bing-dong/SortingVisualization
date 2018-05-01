#ifndef WINDOW_H
#define WINDOW_H

#include "sorting.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void on_button_begin_clicked();
    void timeOut();
    void on_sortingGenegate_clicked();
    void sortDone();
    void setRect(int x, int h);


private:
    Ui::Window *ui;
    void GenerateRandomRect();
    void stopTimer();
    int getSpeed();
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    int RectNum;// 10 - 500;             //排序数目
    QGraphicsRectItem **rectArray; //存放矩形元素指针的数组
    int sceneHeight;
    double sceneWidth;
    QTimer *timer;
    sorting *sort;
    unsigned long int timeCnt = 0;
};

#endif // WINDOW_H
