#include "Update.h"


Update* Update::s_instance;

Update::Update()
{
	Init();
}

Update::~Update()
{
}

Update * Update::GetInstance()
{
	if (!s_instance) {
		s_instance = new Update();
	}
	return s_instance;
}

void Update::Init()
{
	this->damageOfPlayer = 100.0f;
	this->hpOfPlayer = 3000.0f;
	this->damageOfMB1 = 100.0f;
	this->hpOfMB1 = 500.0f;
	this->damageOfEm2 = damageOfMB1 / 2;
	this->hpOfEm2 = hpOfMB1 * 2;
	this->damageOfEm3 = damageOfMB1 * 2;
	this->hpOfEm3 = hpOfMB1;
	this->num_Villager = 0;
	CCLOG("------- Done Update");

}

float Update::getDamageOfPlayer()
{
	return this->damageOfPlayer;
}

float Update::getHPOfPlayer()
{
	return this->hpOfPlayer;
}

float Update::getDamageOfMB1()
{
	return this->damageOfMB1;
}

float Update::getHPOfMB1()
{
	return this->hpOfMB1;
}

float Update::getDamageOfEm2()
{
	return this->damageOfEm2;
}

float Update::getHPOfEm2()
{
	return this->hpOfEm2;
}

float Update::getDamageOfEm3()
{
	return this->damageOfEm3;
}

float Update::getHPOfEm3()
{
	return this->hpOfEm3;
}

Player* Update::getPlayer()
{
	return player;
}

int Update::getCurrentVillager()
{
	return this->num_Villager;
}

void Update::setCurrentVillager(int villager)
{
	this->num_Villager = villager;
}

void Update::setPlayer(Player* player) {
	this->player = player;
}