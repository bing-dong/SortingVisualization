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

    this->setWindowTitle("可视化排序");
    //建立场景
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    sceneHeight = 600;//ui->graphicsView->size().height();
    sceneWidth = 1100;//ui->graphicsView->size().width();
    //设置定时器
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    //connect(sort, SIGNAL(sortDone()), this, SLOT(sortDone()));
}

Window::~Window()
{
    delete ui;
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
    int rectWidth = sceneWidth/RectNum;

    for (int i = 0; i < RectNum; i++)
    {
        rectArray[i] = this->scene->addRect(i*(rectWidth), 600, rectWidth, -rectHeight[i], blackPen, QBrush(Qt::blue));
    }
    delete[] rectHeight;
}

//开始和结束按钮
void Window::on_button_begin_clicked()
{
    if (ui->button_begin->text() == "开始")
    {
        ui->button_begin->setText("结束");
        int sortIndex = ui->sortingWay->currentIndex();
        int sortSpeed = ui->sortingSpeed->currentText().toInt();
        //排序
        sort = new sorting(rectArray, scene, RectNum, sortIndex, sortSpeed);
        //sort->start();
        connect(sort, SIGNAL(sortDone()), this, SLOT(sortDone()));

        //启动定时器
        timer->start(10);
    }
    else if (ui->button_begin->text() == "结束")
    {
        ui->button_begin->setText("开始");
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
    //sort->quit();//停止排序线程
    //sort->wait();
    timer->stop();//停止计时
    timeCnt = 0;
}
