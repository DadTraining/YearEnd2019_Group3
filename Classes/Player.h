#pragma once
#include "Objects.h"
#include "Slash.h"
#define INIT_HP 100
#define INIT_DAMAGE 20 
#define NORMAL_ATTACK_KEY 1
#define SPEAR_ATTACK_KEY 2
#define ULTIMATE_ATTACK_KEY 3


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
	Vec2 getPositionOfSlash();
	//----
	void normalAttack();
	void spearAttack();
	void UltimateAttack();
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
	float getTimeStun();
	float getRatioUlti();
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
	float ratioUlti;
	float timeStun;

};