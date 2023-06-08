#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include"star.h"
#include"Xing.h"
#include<xier.h>
#include"Natasha.h"
#include"Jiachong.h"
#include"Button.h"
#include"Movetimer.h"
#include"Turnmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit关键字  修饰函数 参数 无法自动转换类型 防止隐式转换
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    //各种初始化函数
    void initWindow();
    void initRole();
    void initButton();
    void initManager();
    void initMoveTimer();
    void initPen();
    void buttonBond();
    //实现血条变化
//    void lifebarChanged();

private:
    Ui::MainWidget *ui;

    QGraphicsView GameView;//游戏视图
    QGraphicsScene Scene;//场景
    QPen pen;//画笔

    //图形元素
    QGraphicsPixmapItem Background1;
    QGraphicsPixmapItem* test1;

    //testBtn
    Button* skillAbtn;
    Button* skillBbtn;
    Button* skillCbtn;
    QVBoxLayout* vboxlayout;

    //移动计时器
    MoveTimer *movetimer;

    //BtnGroup
    QButtonGroup* box1 ;

    //testHero
    Xing* xing;
    Xier* xier;
    Natasha* natasha;

    //testEnemy
    Jiachong* jiachong;

    //对象向量组
    vector<Hero*> heroes = {xing,xier,natasha};
    vector<Enemy*> enermies = {jiachong};
    vector<Role*> roles = {xing,xier,natasha,jiachong};

    //一些数值
    int skillPoint = 3;

    //事件处理
    //轮次处理
    TurnManager* turnmanager;
public slots:
    //信号广播槽函数
    void skillAbroadcast();
    void skillBbroadcast();
    void skillCbroadcast();
    //战技点槽函数
    void skillPointUp();
    void skillPointDown();
signals:

};

#endif // MAINWIDGET_H
