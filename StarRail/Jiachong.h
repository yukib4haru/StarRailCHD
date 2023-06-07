#ifndef JIACHONG_H
#define JIACHONG_H

#include"Enemy.h"
#include"star.h"

class Jiachong : public Enemy
{
    Q_OBJECT
public:
    Jiachong();
    void skill(Role* p);
    virtual void bindFunc(){ }

//    - boundingRect():返回人物在场景中的 Bounding Rect(包围盒),用于确定人物的位置与大小。
//    - paint():实现人物的绘制,使用给定的绘图设备(QPainter)进行绘图。
//    virtual QRectF boundingRect() const { /* implement */ }
//    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
//    { /* implement */ }
};

#endif // JIACHONG_H