#include "bird.h"
#include<QString>
Bird::Bird(QWidget *parent) : QWidget(parent)
{
    //加载鸟的所有图片资源
    for (int i=0;i<8;i++) {
        QString str = QString(":/img/bird%1.png").arg(i+1);
        this->m_Bird_Pix.load(str);
    }

    //设置鸟的尺寸
    this->setFixedSize(this->m_Bird_Pix.width(),this->m_Bird_Pix.height());

    //创建菜单
    this->m_Menu = new QMenu();

    connect(this->m_Menu->addAction("退出"),&QAction::triggered,[=](){
        exit(0);
    });

    //创建定时器对象
    this->timer = new QTimer(this);

    connect(timer,&QTimer::timeout,[=](){
        QString str = QString(":/img/bird%1.png").arg(this->min++);
        this->m_Bird_Pix.load(str);
        if(this->min > this->max)
        {
            this->min = 1;
        }
        //掏出自定义信号
        emit changePix();
    });
}

//重写鼠标按下事件
void Bird::mousePressEvent(QMouseEvent *event)
{
    //鼠标按下的时候 记录分量
    //((QWidget*)this->parent())->frameGeometry().topLeft() 获取当前窗口左上角的坐标
    this->m_pos = event->globalPos() - ((QWidget*)this->parent())->frameGeometry().topLeft();

    //鼠标按下状态为真
    this->mouseDown = true;

    //如果是鼠标右键，弹出菜单
    if(event->button() == Qt::RightButton)
    {
        //弹出菜单 弹的位置和鼠标当前位置一致
        this->m_Menu->popup(QCursor::pos());
    }

    //如果菜单 通过别的方式消失，鸟继续飞
    connect(this->m_Menu,&QMenu::aboutToHide,[=](){
        this->mouseDown = false;

    });
}

//重写鼠标移动事件
void Bird::mouseMoveEvent(QMouseEvent *event)
{
    //在移动过程中 反向获取窗口最终移动位置在哪
    emit this->moving(event->globalPos() - this->m_pos);
}

void Bird::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标按下状态为假
    this->mouseDown = false;
}


void Bird::running()
{
    this->timer->start(50);
}
