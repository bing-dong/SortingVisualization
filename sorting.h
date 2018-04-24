#ifndef SORTING_H
#define SORTING_H
#include <QGraphicsRectItem>
#include <QCoreApplication>
#include <QWidget>
#include <QThread>
#include <QTime>

typedef struct node
{
    int height;
//    struct node *next;
//    QGraphicsRectItem rect;
    struct node *next;
}Node;

typedef struct bucket {
    Node *radix[10] = { NULL };
}Bucket;

class sorting: public QObject
{
    Q_OBJECT
public:
    sorting(QGraphicsRectItem **rectArray, QGraphicsScene *&scene, int RectNum, int sortIndex,
            int sortSpeed, double sceneWidth, int sceneHeight);
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
    void sortBegin();

signals:
    void sortDone();

protected:
    void run();
private:
    QGraphicsRectItem **rectArray;
    QGraphicsScene *&scene;
    int RectNum;
    int sortIndex;
    int sortSpeed;
    double sceneWidth;
    int sceneHeight;
};

#endif // SORTING_H
