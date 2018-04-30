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
//    default:
//        break;
//    }
//}

void sorting::sortBegin()
//void sorting::run()
{
    switch (sortIndex) {
    case 0:
        BubbleSort();
        emit sortDone(); break;
    case 1:
        SelectionSort();
        emit sortDone(); break;
    case 2:
        InsertionSort();
        emit sortDone(); break;
    case 3:
        RadixSort();
        emit sortDone(); break;
    case 4:
        HeapSort(rectArray, RectNum);
        emit sortDone(); break;
    case 5:
        MergeSort(rectArray, 0, RectNum-1);
        emit sortDone(); break;
    case 6:
        QuickSort(rectArray, 0, RectNum-1);
        emit sortDone(); break;
    case 7:
        ShellSort(rectArray, RectNum);
        emit sortDone(); break;
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

//基数排序
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
}

//构造最大堆
void sorting::MaxHeapFixDown(QGraphicsRectItem* a[], int i, int n)
{
    int j = 2*i+1;
    int temp = a[i]->boundingRect().height();
    while(j < n)
    {
        if(j+1 < n && -a[j]->boundingRect().height() < -a[j+1]->boundingRect().height())
            ++j;
        if(-temp > -a[j]->boundingRect().height())
            break;
        else
        {
            //a[i] = a[j];
            a[i]->setRect(i*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, a[j]->boundingRect().height()-1);
            scene->update();
            i = j;
            j = 2*i+1;
        }
        Delay_MSec(sortSpeed);
    }
    a[i]->setRect(i*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, temp-1);
    scene->update();
    //a[i] = temp;
}

//堆排序
void sorting::HeapSort(QGraphicsRectItem* a[], int n)//4
{
    for(int i = n/2-1; i >= 0; i--)
        MaxHeapFixDown(a, i, n);
    for(int i = n-1; i >= 1; i--)
    {
        //swap(a[i], a[0]);
        int t = a[i]->boundingRect().height();
        a[i]->setRect(i*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, a[0]->boundingRect().height()-1);
        a[i]->setBrush(QColor(0,255,0));
        a[0]->setRect(0, sceneHeight, sceneWidth/RectNum, t-1);
        scene->update();

        MaxHeapFixDown(a, 0, i);
        Delay_MSec(sortSpeed);
    }
    a[0]->setBrush(QColor(0,255,0));
    scene->update();
}

//两数组合并
void sorting::Merge(QGraphicsRectItem* a[], int left, int mid, int right)
{
    int *height = (int*)malloc(sizeof(int)*(right - left + 1));
    int l = left, m = mid, n = 0;
    while (l < mid && m <= right)
    {
        if (-a[l]->boundingRect().height() < -a[m]->boundingRect().height())
        {
            height[n++] = a[l++]->boundingRect().height();
        }
        else
        {
            height[n++] = a[m++]->boundingRect().height();
        }
        Delay_MSec(sortSpeed);
    }

    while (l < mid)
    {
        height[n++] = a[l++]->boundingRect().height();
        Delay_MSec(sortSpeed);
    }
    while (m <= right)
    {
        height[n++] = a[m++]->boundingRect().height();
        Delay_MSec(sortSpeed);
    }

    for (int k = left, j =  0; k <= right; k++)
    {
        a[k]->setRect(k*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, height[j++]-1);
        scene->update();
        Delay_MSec(sortSpeed);
    }
    free(height);
}

void sorting::MergeSort(QGraphicsRectItem* a[], int left, int right)//5
{
    int mid = (right + left) / 2;

    if (left < right)
    {
        MergeSort(a, left, mid);
        MergeSort(a, mid+1, right);
        Merge(a, left, mid+1, right);
    }
}

void sorting::QuickSort(QGraphicsRectItem* s[], int l, int r)//6
{
    if (l < r)
    {
        int i = l, j = r;
        int x = s[l]->boundingRect().height();

        while (i < j)
        {
            while(i < j && -s[j]->boundingRect().height() >= -x) // 从右向左找第一个小于x的数
            {
                j--;
                Delay_MSec(sortSpeed);
            }

            if(i < j)
            {
                s[i]->setRect(i*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, s[j]->boundingRect().height()-1);
                i++;
                scene->update();
            }

            while(i < j && -s[i]->boundingRect().height() < -x) // 从左向右找第一个大于等于x的数
            {
                i++;
                Delay_MSec(sortSpeed);
            }
            if(i < j)
            {
                s[j]->setRect(j*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, s[i]->boundingRect().height()-1);
                j--;
                scene->update();
            }
        }
        s[i]->setRect(i*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, x-1);
        scene->update();
        QuickSort(s, l, i - 1); // 递归调用
        QuickSort(s, i + 1, r);
    }
}

void sorting::ShellSort(QGraphicsRectItem* ary[], int len)//7
{
    for (int gap = len/2; gap != 0; gap /= 2)
        {
            for (int i = gap; i < len; i++)
            {
                if (-ary[i]->boundingRect().height() < -ary[i-gap]->boundingRect().height())
                {
                    int k = i - gap;
                    int tmp = ary[i]->boundingRect().height();
                    while (k >= 0 && -ary[k]->boundingRect().height() > -tmp)
                    {
                        ary[k+gap]->setRect((k+gap)*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, ary[k]->boundingRect().height()-1);
                        ary[k]->setRect(k*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, 0);
                        scene->update();
                        k -= gap;
                        Delay_MSec(sortSpeed);
                    }
                    ary[k+gap]->setRect((k+gap)*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, tmp-1);
                    scene->update();
                }
            }
        }
}

void sorting::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


