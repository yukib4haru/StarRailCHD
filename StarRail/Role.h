#ifndef ROLE_H
#define ROLE_H

#include<star.h>

class Role:public QObject,public QGraphicsPixmapItem
{
    //QObject必须放在前面
    //QGraphicsPixmapItem不含信号和槽
    Q_OBJECT
public:
    Role(){ }
    Role(QString name1,int hp1,int att1,int speed1,int shield1,int label1,QString skillAiconPath1/*,QString skillBiconPath1*/);
    ~Role();

    virtual void bindFunc()=0;

    //死亡判定
    void uRdead();

    //私有变量接口
    int getAtt(){return att;}
    int getMaxiumHealth(){return maximumHealth;}
    int getSpeed(){return speed;}
    QString getName(){return name;}
    QString getskillAiconPath(){return skillAiconPath;}
    QString getskillBiconPath(){return skillBiconPath;}
    QString getskillCiconPath(){return skillCiconPath;}

    //返回类型信息以便强制类型转换
    virtual string getType() = 0;

private:
    QString name;
    QString skillAiconPath;
    QString skillBiconPath;
    QString skillCiconPath;
    int hp;
    int maximumHealth;
    int att;
    int speed;
    int shield;
    int label;
    bool isAlive;

signals:
    //我被杀了
    void imKilled(Role* p);
public slots:
    //显示角色基本状态 用于调试
    void showBasicStatus();
    //收到伤害
    void beAttacked(int damage);
    //获得增益效果
    void beGivenShieldBuff(int effect);
    //收到治疗效果
    void beCured(int health);
};


#endif // ROLE_H
