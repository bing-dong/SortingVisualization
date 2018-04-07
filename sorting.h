#ifndef SORTING_H
#define SORTING_H
#include <QGraphicsRectItem>
#include <QCoreApplication>
#include <QWidget>
#include <QThread>
#include <QTime>

class sorting: public QObject
{
    Q_OBJECT
public:
    sorting(QGraphicsRectItem **rectArray, QGraphicsScene *scene, int RectNum, int sortIndex, int sortSpeed, QObject *parent = 0);
    ~sorting();
    void ShellSort();   //combo index is 7
    void QuickSort();   //6
    void MergeSort();   //5
    void HeapSort();    //4
    void RadixSort();   //3
    void InsertionSort();//2
    void SelectionSort();//1
    void BubbleSort();  //0
    void AllSort();     //8
    void Delay_MSec(unsigned int msec);

signals:
    void sortDone();

protected:
    //void run();
private:
    QGraphicsRectItem **rectArray;
    QGraphicsScene * &scene;
    int RectNum;
    int sortIndex;
    int sortSpeed;
};

#endif // SORTING_H
