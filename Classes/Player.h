#pragma once
#include "Objects.h"
#include "Slash.h"
#define TIME_ONE_ATTACK 0.1f
#define TIME_ONE_HIT 0.1f
#define TIME_ONE_IDLE 0.2f
#define TIME_ONE_RUN 0.1f
#define TIME_ONE_DEAD 0.26f
#define TIME_ONE_WALK 0.1f
#define INIT_HP 100
#define INIT_DAMAGE 20 

class Player : public Objects
{
public:
	// An integer to determine if the player release all the keyCode
	int m_numberOfKeyPress = 0;
	Player(Scene* scene);
	~Player();
	void init();
	void update(float deltaTime);
	void addPhysic();

	void setSprite(Sprite* sprite);
	void setAttackAnimate(Animate* attackAnimate);
	void setIdleAnimate(Animate* idleAnimate);
	void setHitAnimate(Animate* hitAnimate);
	void setRunAnimate(Animate* runAnimate);
	void setDeadAnimate(Animate* deadAnimate);
	void setHP(float hP);
	void setDamage(float damage);

	//----
	void normalAttack();
	void increaseVillager(int num);
	void CheckUpdate();
	void gotHit();
	//----

	Sprite* getSprite();
	Animate* getAttackAnimate();
	Animate* getIdleAnimate();
	Animate* getHitAnimate();
	Animate* getRunAnimate();
	Animate* getDeadAnimate();
	float getHP();
	float getDamage();

private:
	Sprite* playerSprite;
	Animate *attackAnimate, *idleAnimate, *hitAnimate, *runAnimate, *deadAnimate;
	float hP, damage;
	Slash* m_slash;
	Scene* targetScene;
	int villagersNum;
};