#include "Turnmanager.h"
#include"star.h"
#include"Hero.h"
#include"Enemy.h"
#include"Role.h"

#include"xier.h"

TurnManager::TurnManager(vector<Role*> heroes1,vector<Role*> enemies1,vector<Role*> roles1)
{
    heroes=heroes1;
    enemies=enemies1;
    roles=roles1;
}

void TurnManager::init()
{
    //先按速度大小进行排序
    sort(roles.begin(), roles.end(), [](Role* c1, Role* c2){
        return c1->getSpeed() > c2->getSpeed();
    });

    currentTurn = 1;
    turnIterator = roles.begin();   //指向第一个角色

    curRole =  *turnIterator;   // 可选,初始化当前角色

    std::srand(std::time(nullptr));  // 初始化随机数种子

    //之前这一行代码有问题，访问了空容器
    //真正的问题是Role* Hero* 转化继承派生的问题……

}

void TurnManager::update()
{
    // 如果是敌方角色,处理输入事件释放技能
    if (std::find(enemies.begin(), enemies.end(), curRole) != enemies.end())
    {
        // 处理敌方技能等
        int cur = rand()%3;
        heroes[cur]->beAttacked(curRole->getAtt());
    }

    // 执行当前角色的行动
    //    curRole->act();

    // 迭代器指向下一个角色
    turnIterator++;

    if (turnIterator == roles.end()) {
        currentTurn++;
        //实现从大到小排序，使用lamda函数？
        sort(roles.begin(), roles.end(), [](Role* c1, Role* c2){
            return c1->getSpeed() > c2->getSpeed();
        });
        turnIterator = roles.begin();
    }

    // 获取当前角色
    curRole = *turnIterator;

    //调试用
    qDebug()<<"现在是第"<<currentTurn<<"回合\n";
}
