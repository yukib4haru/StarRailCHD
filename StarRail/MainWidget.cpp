#include "MainWidget.h"
#include "ui_MainWidget.h"

#include"star.h"

#include"Button.h"

#include"Role.h"
#include"Hero.h"
#include"Xing.h"
#include"Natasha.h"
#include"Enemy.h"
#include"Jiachong.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    initRole();     //初始化人物 必须放在初始化窗口前面
    initManager();  //初始化事件，应该要放在人物后边吧
    initWindow();   //初始化窗口
    initButton();   //初始化按钮
    buttonBond();   //连接
}


MainWidget::~MainWidget()
{
    delete ui;
}

//初始化事件
void MainWidget::initManager()
{
    turnmanager = new TurnManager(heroes,enermies,roles);
    turnmanager->init();
}

//初始化人物
void MainWidget::initRole()
{
    Jiachong* jiachongTemp;
    jiachongTemp = new Jiachong();
    shared_ptr<Jiachong> jiachong(jiachongTemp);
    jiachong->bindFunc();

    Xing* xingTemp;
    xingTemp = new Xing();
    shared_ptr<Xing> xing(xingTemp);
    xing->bindFunc();

    Xier* xierTemp;
    xierTemp = new Xier();
    shared_ptr<Xier> xier(xierTemp);
    xier->bindFunc();

    Natasha* natashaTemp;
    natashaTemp = new Natasha();
    shared_ptr<Natasha> natasha(natashaTemp);
    natasha->bindFunc();
}

//初始化窗口
void MainWidget::initWindow()
{
    //设置窗口大小
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置图标
    this->setWindowIcon(QIcon(":/Image/StarRail.ico"));
    //设置视图
    GameView.setSceneRect(QRect(0,0,GAME_WIDTH,GAME_HEIGHT));
    //设置场景
    Scene.setSceneRect(QRect(0,0,GAME_WIDTH,GAME_HEIGHT));
    //设置背景图片
    Background1.setPixmap(QPixmap(":/Image/BK2.png"));

    //图片元素添加到场景
    Scene.addItem(&Background1);

    //添加人物
    Scene.addItem(xing.get());
    Scene.addItem(xier.get());
    Scene.addItem(natasha.get());
    Scene.addItem(jiachong.get());

    //场景添加到视图 or 设置视图场景
    GameView.setScene(&Scene);
    //设置视图的父亲
    GameView.setParent(this);
    GameView.showFullScreen();
    GameView.show();
}

//初始化按钮
void MainWidget::initButton()
{
    //试创建按钮A
    this->skillAbtn = new Button(this);
    this->skillAbtn->setIcon(QIcon(":/Image/xierQ1.png"));//设置技能图标
    this->skillAbtn->setIconSize(QSize(300,300));//设置技能大小
    //使其成为一个可选按钮
    skillAbtn->setCheckable(true);

    //设置透明边框
    this->skillAbtn->setFlat(true);
    this->skillAbtn->setFocusPolicy(Qt::NoFocus);
    //移动按钮
    this->skillAbtn->move(width()*3/4,height()*2/3);

    //同理创建B
    this->skillBbtn = new Button(this);
    this->skillBbtn->setIcon(QIcon(":/Image/xierE0.png"));
    this->skillBbtn->setIconSize(QSize(151,151));
    this->skillBbtn->setFlat(true);
    this->skillBbtn->setFocusPolicy(Qt::NoFocus);
    this->skillBbtn->move(width()*3/4 - 50,height()*2/3 - 75);
    skillBbtn->setCheckable(true);

    //顺序错了，还没创建B怎么连接呢？

    //使两个按钮自动互斥
    skillAbtn->setAutoExclusive(true);
//  skillAbtn->setChecked(true);
    skillBbtn->setAutoExclusive(true);
}

//信号和槽连接
void MainWidget::buttonBond()
{
    //实现A按钮
    connect(skillAbtn,&Button::clicked,this,&MainWidget::skillAbroadcast);
    connect(skillAbtn,&Button::clicked,jiachong.get(),&Jiachong::showBasicStatus);
    connect(skillAbtn,&Button::clicked,this,&MainWidget::skillPointUp);
    //接收到的信号为星，则由星发动
    connect(xing.get(),&Xing::skillAsignal,xing.get(),&Xing::skillA);
    connect(xing.get(),&Xing::skillAdamage,jiachong.get(),&Jiachong::beAttacked);
    //接收到的信号为希尔，则由希尔发动
    connect(xier.get(),&Xier::skillAsignal,xier.get(),&Xier::skillA);
    connect(xier.get(),&Xier::skillAdamage,jiachong.get(),&Jiachong::beAttacked);
    //接收到的信号为娜塔莎，则由娜塔莎发动
    connect(natasha.get(),&Natasha::skillAsignal,natasha.get(),&Natasha::skillA);
    connect(natasha.get(),&Natasha::skillAdamage,jiachong.get(),&Jiachong::beAttacked);
    //实现B按钮
    connect(skillBbtn,&Button::clicked,this,&MainWidget::skillBbroadcast);
    connect(skillBbtn,&Button::clicked,jiachong.get(),&Jiachong::showBasicStatus);
    connect(skillBbtn,&Button::clicked,this,&MainWidget::skillPointDown);
    //接收到的信号为星，则由星发动
    connect(xing.get(),&Xing::skillBsignal,xing.get(),&Xing::skillB);
    connect(xing.get(),&Xing::skillBbuff,xing.get(),&Xing::beGivenShieldBuff);
    //接收到的信号为希尔，则由希尔发动
    connect(xier.get(),&Xier::skillBsignal,xier.get(),&Xier::skillB);
    connect(xier.get(),&Xier::skillBdamage,jiachong.get(),&Jiachong::beAttacked);
    //接收到的信号为娜塔莎，则由娜塔莎发动
    connect(natasha.get(),&Natasha::skillBsignal,natasha.get(),&Natasha::skillB);
    connect(natasha.get(),&Natasha::skillBcure,jiachong.get(),&Jiachong::beCured);
}

void MainWidget::skillAbroadcast()
{
    qDebug()<<"是谁的A技能的信号被发送了呢\n";
    if(turnmanager->getCurRole()==xing)
    {
        emit xing->skillAsignal();
        qDebug()<<"发送星的A技能的信号\n";
    }
    if(turnmanager->getCurRole()==natasha)
    {
        emit natasha->skillAsignal();
        qDebug()<<"发送娜塔莎的A技能的信号\n";
    }
    if(turnmanager->getCurRole()==xier)
    {
        emit xier->skillAsignal();
        qDebug()<<"发送希尔的A技能的信号\n";
    }
    turnmanager->update();
}

void MainWidget::skillBbroadcast()
{
    if(skillPoint>0)
    {
        if(turnmanager->getCurRole()==xing)
        {
            emit xing->skillBsignal();
            qDebug()<<"发送星的B技能的信号\n";
        }
        if(turnmanager->getCurRole()==natasha)
        {
            emit natasha->skillBsignal();
            qDebug()<<"发送娜塔莎的B技能的信号\n";
        }
        if(turnmanager->getCurRole()==xier)
        {
            emit xier->skillBsignal();
            qDebug()<<"发送希尔的B技能的信号\n";
        }
    }
    else
    {
        qDebug()<<"战技点不足\n";
    }
    turnmanager->update();
}

void MainWidget::skillCbroadcast()
{
    if(turnmanager->getCurRole()==xing)
    {
        emit xing->skillCsignal();
        qDebug()<<"发送星的C技能的信号\n";
    }
    if(turnmanager->getCurRole()==natasha)
    {
        emit natasha->skillCsignal();
        qDebug()<<"发送娜塔莎的C技能的信号\n";
    }
    if(turnmanager->getCurRole()==xier)
    {
        emit xier->skillCsignal();
        qDebug()<<"发送希尔的C技能的信号\n";
    }
    turnmanager->update();
}

void MainWidget::skillPointUp()
{
    if(skillPoint<SKILL_POINT_MAX) skillPoint++;
    qDebug()<<"战技点："<<skillPoint<<"\n";
}

void MainWidget::skillPointDown()
{
    if(skillPoint>SKILL_POINT_LEAST) skillPoint--;
    qDebug()<<"战技点："<<skillPoint<<"\n";
}
