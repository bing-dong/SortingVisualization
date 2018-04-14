#include "sorting.h"
#include <QGraphicsScene>
#include <QDebug>

sorting::sorting(QGraphicsRectItem **rectArray, QGraphicsScene *&scene, int RectNum,
                 int sortIndex, int sortSpeed, double sceneWidth, int sceneHeight)
    :rectArray(rectArray), scene(scene), RectNum(RectNum), sortIndex(sortIndex),
      sortSpeed(sortSpeed), sceneWidth(sceneWidth), sceneHeight(sceneHeight)
{
//    this->rectArray = rectArray;
//    this->scene = scene;
//    this->RectNum = RectNum;
//    this->sortIndex = sortIndex;
//    this->sortSpeed = sortSpeed;
//    this->sceneWidth = sceneWidth;
//    this->sceneHeight = sceneHeight;
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

void sorting::sortBegin()
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

sorting::~sorting()
{

}

void sorting::BubbleSort()  //0
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    for (int i=0; i<RectNum-1; i++)
    {
        for (int j=0; j<RectNum-1-i; j++)
        {
            if (-rectArray[j]->boundingRect().height() > -rectArray[j+1]->boundingRect().height())
            {
                QGraphicsRectItem *rect = rectArray[j];
                scene->removeItem(rectArray[j]);
                //rectArray[j]->boundingRect().height()获取的高度是负值，而且获取的并不是真实高度，
                //获取值-1的绝对值才是真实的高度
                rectArray[j] = scene->addRect(j*sceneWidth/RectNum, sceneHeight, sceneWidth/RectNum,
                               rectArray[j+1]->boundingRect().height()-1, blackPen, QBrush(Qt::blue));
                scene->removeItem(rectArray[j+1]);
                rectArray[j+1] = scene->addRect((j+1)*sceneWidth/RectNum, sceneHeight, sceneWidth/RectNum,
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
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    for (int i=0; i<RectNum-1; i++)
    {
        int pos = i;
        for (int j=i; j<RectNum; j++)
        {
            if (-rectArray[j]->boundingRect().height() < -rectArray[pos]->boundingRect().height())
            {
                pos = j;
            }
            //Delay_MSec(sortSpeed);
        }

        rectArray[pos]->setBrush(QColor(0,255,0));//找到最小值标记绿色
        scene->update();
        Delay_MSec(sortSpeed*(RectNum-i));//等效位内层for循环的延时

        if (pos != i)
        {
            QGraphicsRectItem *rect = rectArray[i];
            scene->removeItem(rectArray[i]);
            rectArray[i] = scene->addRect(i*sceneWidth/RectNum, sceneHeight, sceneWidth/RectNum,
                           rectArray[pos]->boundingRect().height()-1, blackPen, QBrush(Qt::green));
            scene->removeItem(rectArray[pos]);
            rectArray[pos] = scene->addRect((pos)*sceneWidth/RectNum, sceneHeight, sceneWidth/RectNum,
                           rect->boundingRect().height()-1, blackPen, QBrush(Qt::blue));
            scene->update();
        }
        else
        {
            rectArray[pos]->setBrush(QColor(0,255,0));
            scene->update();
        }
    }
    rectArray[RectNum-1]->setBrush(QColor(0,255,0));
    //scene->update();
    emit sortDone();
}

void sorting::InsertionSort()//2
{

}

void sorting::RadixSort()//3
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    for (int i=1; i<RectNum; i++)
    {
        QGraphicsRectItem *rect = rectArray[i];
        scene->removeItem(rectArray[i]);

        for (int j=0; j<i; j++)
        {
            if (-rectArray[i]->boundingRect().height() < -rectArray[j]->boundingRect().height())
            {

            }
            //
        }
    }
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


