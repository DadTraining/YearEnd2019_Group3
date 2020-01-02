#pragma once
#include "Objects.h"
#include "Slash.h"
#define TIME_ONE_ATTACK 0.1f
#define TIME_ONE_HIT 0.1f
#define TIME_ONE_IDLE 0.2f
#define TIME_ONE_RUN 0.1f
#define TIME_ONE_DEAD 0.26f
#define TIME_ONE_WALK 0.1f

class MiniBoss01 : public Objects
{
public:
	MiniBoss01(Scene* scene);
	~MiniBoss01();
	void init();
	void update(float deltaTime);

	void setSprite(Sprite* sprite);
	void setAttackAnimate(Animate* attackAnimate);
	void setIdleAnimate(Animate* idleAnimate);
	void setHitAnimate(Animate* hitAnimate);
	void setRunAnimate(Animate* runAnimate);
	void setDeadAnimate(Animate* deadAnimate);
	void setHP(float hP);
	void setDamage(float damage);
	void setPosSpawn(Point point);
	

	Sprite* getSprite();
	Animate* getAttackAnimate();
	Animate* getIdleAnimate();
	Animate* getHitAnimate();
	Animate* getRunAnimate();
	Animate* getDeadAnimate();
	float getHP();
	float getDamage();
	Point getPosSpawn();
	//---
	//Attack
	void normalAttack();
	void gotHit();
	// Add physics
	void addPhysic();
	void setIndex(int index);
	void Die();
	//---
	
private:
	Sprite* sprite;
	Animate *attackAnimate, *idleAnimate, *hitAnimate, *runAnimate, *deadAnimate;
	float hP, damage;
	Slash* m_slash;
	Scene* targetScene;
	Point posSpawn;
};