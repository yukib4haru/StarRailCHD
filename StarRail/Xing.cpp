#include "Xing.h"
#include"star.h"

Xing::Xing():Hero("星",100,15,7,0,2,":/Image/XingQ0.png")
{
    this->setPixmap(QPixmap(":/Image/Xing.png"));   // 设置图像
    this->setXSite(50);
    this->setYSite(-50);
    this->setPos(this->getXSite(),this->getYSite());

    this->lifebar->setWidth(400);
    this->lifebar->setBarXSite(getXSite()+100);
    this->lifebar->setBarYSite(getYSite()+100);
    this->lifebar->setRect(lifebar->getBarXSite(),lifebar->getBarYSite(),lifebar->getWidth(),10);

    this->shieldbar->setWidth(0);
    this->shieldbar->setBarXSite(getXSite()+100);
    this->shieldbar->setBarYSite(getYSite()+100-10);
    this->shieldbar->setRect(shieldbar->getBarXSite(),shieldbar->getBarYSite(),shieldbar->getWidth(),10);
}

Xing::~Xing()
{

}

void Xing::skillA()
{
    qDebug()<<"星释放A技能\n";
    emit this->skillAdamage(getAtt());
}

void Xing::skillB()
{
    qDebug()<<"星释放B技能\n";
    emit this->skillBbuff(getAtt());
}

void Xing::skillC()
{

}

void Xing::setDistance(float moveDistanceX,float moveDistanceY)
{
    this->setXMove(moveDistanceX);
    this->setYMove(moveDistanceY);
}

void Xing::moveTo()
{
    int x=this->getXSite()+this->getXMove();
    this->setXSite(x);
    int y=this->getYSite()+this->getYMove();
    this->setYSite(y);
    this->setPos(x,y);
}
