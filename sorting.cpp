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

//此函数可设置矩形位置和大小
//rectArray[0]->setRect(0, sceneHeight, sceneWidth/RectNum, -30);

void sorting::BubbleSort()  //0
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    QGraphicsRectItem *rect = NULL;

    for (int i=0; i<RectNum-1; i++)
    {
        for (int j=0; j<RectNum-1-i; j++)
        {
            if (-rectArray[j]->boundingRect().height() > -rectArray[j+1]->boundingRect().height())
            {
                rect = rectArray[j];
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
    delete rect;
    rectArray[0]->setBrush(QColor(0,255,0));
    scene->update();
    emit sortDone();
}

void sorting::SelectionSort()//1
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    QGraphicsRectItem *rect = NULL;

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
            rect = rectArray[i];
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
    delete rect;
    rectArray[RectNum-1]->setBrush(QColor(0,255,0));
    //scene->update();
    emit sortDone();
}

void sorting::InsertionSort()//2
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    QGraphicsRectItem *rect = NULL;

    for (int i=1; i<RectNum; i++)
    {
        rect = rectArray[i];
        for (int j=i; j>0; j--)
        {
            //此位置比前一位置的元素小，则向前插入
            if (-rect->boundingRect().height() < -rectArray[j-1]->boundingRect().height())
            {
                scene->removeItem(rectArray[j]);
                rectArray[j] = scene->addRect(j*sceneWidth/RectNum, sceneHeight, sceneWidth/RectNum,
                               rectArray[j-1]->boundingRect().height()-1, blackPen, QBrush(Qt::green));
                scene->removeItem(rectArray[j-1]);
                rectArray[j-1] = scene->addRect((j-1)*sceneWidth/RectNum, sceneHeight, sceneWidth/RectNum,
                               rect->boundingRect().height()-1, blackPen, QBrush(Qt::red));
                scene->update();
                Delay_MSec(sortSpeed);
                rectArray[j-1]->setBrush(QColor(0,255,0));
            }
            //当最后一个最高时，在上述程序中将其移除，但没有填补，在此进行原处插入
            else if (i == RectNum-1 && j == RectNum-1)
            {
                rectArray[j] = scene->addRect(j*sceneWidth/RectNum, sceneHeight, sceneWidth/RectNum,
                                              rectArray[j]->boundingRect().height()-1, blackPen, QBrush(Qt::green));
            }
        }
    }


    rectArray[0]->setBrush(QColor(0,255,0));
    scene->update();
    delete rect;
    emit sortDone();
}

//RadixSort的添加节点函数
void addNode(Node* &node, int height)
{
    Node *t = node;
    if (t == NULL)
    {
        node = (Node*)malloc(sizeof(Node));
        node->height = height;
        node->next = NULL;
    }
    else
    {
        while (t->next)
        {
            t = t->next;
        }
        t->next = (Node*)malloc(sizeof(Node));
        t->next->height = height;
        t->next->next = NULL;
    }

}

void sorting::RadixSort()//3
{
    Bucket bucket;

    for (int i = 1; i <= 100; i *= 10)
    {
        //分配
        for (int j = 0; j<RectNum; j++)
        {
            int n = ((int)(-rectArray[j]->boundingRect().height()) / i) % 10 ;
            addNode(bucket.radix[n], rectArray[j]->boundingRect().height());//创建值为a[j]的节点，并将其加入头节点为radix[n]的链表中
            Delay_MSec(sortSpeed);
        }

        //回收
        int n = 0;
        for (int j = 0; j<10; j++)
        {
            Node *t = bucket.radix[j];
            Node *temp;
            while (t != NULL)
            {
                temp = t;
                rectArray[n++]->setRect(n*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, t->height-1);
                scene->update();
                t = t->next;
                free(temp);
            }
            bucket.radix[j] = NULL;
            Delay_MSec(sortSpeed);
        }
    }
    emit sortDone();
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


