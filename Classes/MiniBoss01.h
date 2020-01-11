#pragma once
#include "Objects.h"
#include "Slash.h"
#define SKELETON_DAMGE 100.0f
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
	void setAIforEnemy();
	
	// Got stun
	void Stun();

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
	void gotHit(int damage);
	// Add physics
	void addPhysic();
	void setIndex(int index);
	void Die();
	void setAlive(bool isAlive);
	bool getAlive();

	void createSlash();
	Slash* getSlash();
	//---
	
private:
	Sprite* sprite;
	Animate *attackAnimate, *idleAnimate, *hitAnimate, *runAnimate, *deadAnimate;
	float hP, damage;
	Slash* m_slash;
	Scene* targetScene;
	Point posSpawn;
	int price;
	bool isAlive;
};