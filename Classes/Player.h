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
	void createSlash();

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
	void gotHit(int damage);
	Slash* getSlash();
	//----

	Sprite* getSprite();
	Animate* getAttackAnimate();
	Animate* getIdleAnimate();
	Animate* getHitAnimate();
	Animate* getRunAnimate();
	Animate* getDeadAnimate();
	Animate* getSkillAAnimate();
	Animate* getSkillBAnimate();
	
	float getHP();
	float getDamage();
	void Die();
	int getVillagersNum();

	// getAlive
	void setAlive(bool isAlive);
	bool getAlive();

private:
	Sprite* playerSprite;
	Animate *attackAnimate, *idleAnimate, *hitAnimate, *runAnimate, *deadAnimate, *skillAAnimate, *skillBAnimate;
	float hP, damage;
	Slash* m_slashNormal;
	Slash* m_slashSpear;
	Slash* m_slashUltimate;
	Scene* targetScene;
	int villagersNum;
	bool isAlive;
};