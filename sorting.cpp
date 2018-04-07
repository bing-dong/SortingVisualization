#include "sorting.h"
#include <QGraphicsScene>
#include <QDebug>

sorting::sorting(QGraphicsRectItem **rectArray, QGraphicsScene *scene, int RectNum, int sortIndex, int sortSpeed, QObject *parent)
    :rectArray(rectArray), scene(scene), RectNum(RectNum), sortIndex(sortIndex), sortSpeed(sortSpeed)
{
    switch (sortIndex) {
    case 0:
        BubbleSort(); break;
    case 1:
        SelectionSort(); break;
    case 2:
        InsertionSort(); break;
    case 3:
        RadixSort(); break;
    case 4:
        HeapSort(); break;
    case 5:
        MergeSort(); break;
    case 6:
        QuickSort(); break;
    case 7:
        ShellSort(); break;
    case 8:
        AllSort(); break;
    default:
        break;
    }
}

//void sorting::run()
//{
//    switch (sortIndex) {
//    case 0:
//        BubbleSort(); break;
//    case 1:
//        SelectionSort(); break;
//    case 2:
//        InsertionSort(); break;
//    case 3:
//        RadixSort(); break;
//    case 4:
//        HeapSort(); break;
//    case 5:
//        MergeSort(); break;
//    case 6:
//        QuickSort(); break;
//    case 7:
//        ShellSort(); break;
//    case 8:
//        AllSort(); break;
//    default:
//        break;
//    }
//}

sorting::~sorting()
{

}

void sorting::BubbleSort()  //0
{
    for (int i=0; i<RectNum-1; i++)
    {
        for (int j=0; j<RectNum-1-i; j++)
        {
            if (-rectArray[j]->boundingRect().height() > -rectArray[j+1]->boundingRect().height())
            {
                QPen blackPen(Qt::black);
                blackPen.setWidth(1);

                QGraphicsRectItem *rect = rectArray[j];
                scene->removeItem(rectArray[j]);
                //rectArray[j]->boundingRect().height()获取的高度是负值，而且获取的并不是真实高度，
                //获取值-1的绝对值才是真实的高度
                rectArray[j] = scene->addRect(j*1100/RectNum, 600, 1100/RectNum,
                               rectArray[j+1]->boundingRect().height()-1, blackPen, QBrush(Qt::blue));

                scene->removeItem(rectArray[j+1]);
                rectArray[j+1] = scene->addRect((j+1)*1100/RectNum, 600, 1100/RectNum,
                               rect->boundingRect().height()-1, blackPen, QBrush(Qt::green));
                scene->update();
            }
            else
            {
                rectArray[j]->setBrush(QColor(0,0,255));
                rectArray[j+1]->setBrush(QColor(0,255,0));
                scene->update();
            }
            Delay_MSec(sortSpeed);
        }
    }
    rectArray[0]->setBrush(QColor(0,255,0));
    scene->update();
    emit sortDone();
}

void sorting::SelectionSort()//1
{

}

void sorting::InsertionSort()//2
{

}

void sorting::RadixSort()//3
{

}

void sorting::HeapSort()//4
{

}

void sorting::MergeSort()//5
{

}

void sorting::QuickSort()//6
{

}

void sorting::ShellSort()//7
{

}

void sorting::AllSort()//8
{

}

void sorting::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


