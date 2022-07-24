#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include<QPixmap>
#include<QTimer>
#include<QPoint>
#include<QMouseEvent>
#include<QMenu>
class Bird : public QWidget
{
    Q_OBJECT
public:
    explicit Bird(QWidget *parent = nullptr);

    QPixmap m_Bird_Pix;//鸟显示的图片

    int min = 1;
    int max = 8;
    //定时器
    QTimer * timer;
    //执行动画函数
    void running();

    //记录分量坐标
    QPoint m_pos;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);

    //鼠标按下状态
    bool mouseDown = false;

    //右键菜单，帮助实现退出
    QMenu * m_Menu;

signals:
    //自定义信号
    void changePix();

    //自定义信号 拖拽后主场景应该移动的位置
    void moving(QPoint point);

};

#endif // BIRD_H
