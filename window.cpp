#include "window.h"
#include "ui_window.h"
#include <QTime>
#include <QBrush>
#include <QDebug>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    this->setWindowTitle("排序可视化");
    //建立场景
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    sceneHeight = 600;
    sceneWidth = 1100;

    //设置定时器
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    //开始按钮不可用
    ui->button_begin->setDisabled(true);
}


void Window::GenerateRandomRect()
{
    rectArray = new QGraphicsRectItem*[RectNum];
    int *rectHeight = new int[RectNum];

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < RectNum; i++)
    {
        //生成随机高度
        rectHeight[i] = 1+qrand()%(sceneHeight-2);
    }

    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    double rectWidth = sceneWidth/RectNum;

    for (int i = 0; i < RectNum; i++)
    {
        rectArray[i] = this->scene->addRect(i*(rectWidth), sceneHeight, rectWidth, -rectHeight[i], blackPen, QBrush(Qt::blue));
    }
    delete[] rectHeight;
}

//开始和结束按钮
void Window::on_button_begin_clicked()
{
    if (ui->button_begin->text() == "开始")
    {
        ui->button_begin->setText("结束");
        //排序时禁止‘排序生成’按钮
        ui->sortingGenegate->setDisabled(true);
        int sortIndex = ui->sortingWay->currentIndex();
        int sortSpeed = getSpeed();

        sort = new sorting(rectArray, scene, RectNum, sortIndex, sortSpeed, sceneWidth, sceneHeight);
        //Qt::BlockingQueuedConnection多线程中排队
        connect(sort, SIGNAL(setRect(int,int)), this, SLOT(setRect(int,int)), Qt::BlockingQueuedConnection);
        connect(sort, SIGNAL(sortDone()), this, SLOT(sortDone()));
        sort->start();  //线程开始排序
        //启动定时器
        timer->start(10);
    }
    else if (ui->button_begin->text() == "结束")
    {
        ui->button_begin->setText("开始");
        //排序结束启用‘排序生成’按钮
        ui->sortingGenegate->setEnabled(true);
        //开始按钮不可用
        ui->button_begin->setDisabled(true);
        sort->quit();
        stopTimer();
    }
}

void Window::on_sortingGenegate_clicked()
{
    if (rectArray != NULL)
    scene->clear();
    //读取排序数目
    RectNum = ui->sortingNum->text().toInt();

    if (rectArray != NULL)
    {
        delete[] rectArray;
        rectArray = NULL;
    }
    this->GenerateRandomRect();
    scene->update();

    //开始按钮可用
    ui->button_begin->setEnabled(true);
}

int Window::getSpeed()
{
    switch (ui->sortingSpeed->currentText().toInt()){
        case 1: return 100;
        case 2: return 10;
        case 3: return 1;
        default: return 1;
    }
}

void Window::setRect(int x, int h)
{
    rectArray[x]->setRect(x*(sceneWidth/RectNum), sceneHeight, sceneWidth/RectNum, h);
    scene->update();
}

void Window::timeOut()
{
    ui->lable_time->setText(QString::number(timeCnt));
    timeCnt++;
}

void Window::stopTimer()
{
    timer->stop();//停止计时
    ui->lable_time->setText(QString::number(0));
    timeCnt = 0;
}

void Window::sortDone()
{
//    sort->terminate();
//    sort->wait();
    sort->quit();
    timer->stop();//停止计时
    timeCnt = 0;
}

Window::~Window()
{
    delete ui;
//    sort->terminate();
//    sort->wait();
}
