#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QIcon>
#include<QDesktopWidget>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/img/birdIcon.ico"));

    //创建鸟对象
    this->m_Bird = new Bird;

    //将鸟对象显示到窗口中
    this->m_Bird->setParent(this);

    //设置窗口尺寸
    this->setFixedSize(this->m_Bird->width(),this->m_Bird->height());

    //启动定时器
    this->m_Bird->running();

    //监听鸟切图信号
    connect(this->m_Bird,&Bird::changePix,[=](){
        update();
    });

    //监听鸟拖拽移动的信号
    connect(this->m_Bird,&Bird::moving,[=](QPoint point){
        this->move(point);
        m_Auto_Pos = point;//鼠标拖拽的时候更新当前窗口的位置
    });

    //创建定时器对象
    this->timer = new QTimer(this);

    //启动定时器
    this->timer->start(30);

    //获取屏幕
    QDesktopWidget * desk = QApplication::desktop();

    //监听定时器
    connect(timer,&QTimer::timeout,[=]()
    {
        //如果鼠标没有按下，才向前自动移动
        if(this->m_Bird->mouseDown != true)
        {
            this->m_Auto_Pos.setX(this->m_Auto_Pos.x()+5);
        }
        if(this->m_Auto_Pos.x()>desk->width())
        {
            this->m_Auto_Pos.setX(-this->m_Bird->width());
        }

        //窗口同步移动
        this->move(this->m_Auto_Pos);
    });

    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置透明窗体 120号属性
    this->setAttribute(Qt::WA_TranslucentBackground);

    //设置窗口顶层
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);

    //设置起始Y位置
    this->m_Auto_Pos.setY(desk->height()*0.5-this->m_Bird->height()*0.5);

}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0,0,this->m_Bird->m_Bird_Pix);
}

MainScene::~MainScene()
{
    delete ui;
}

