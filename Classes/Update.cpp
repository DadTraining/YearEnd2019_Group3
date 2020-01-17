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
	this->path = "Resources/InformationOfPlayer.txt";
	this->pathStateSkill = "Resources/StateSkill.txt";
	readFile(path);

	this->hpOfPlayer = allData[0];
	this->damageOfPlayer = allData[1];
	this->sumVillages = allData[2];
	this->conditionUlti = allData[3];
	this->stunTime = allData[4];

	readFileStateSkill(pathStateSkill);

	this->stateSlow = states[0];
	this->stateUlti = states[1];

	this->damageOfMB1 = 100.0f;
	this->hpOfMB1 = 500.0f;
	this->damageOfEm2 = damageOfMB1 / 2;
	this->hpOfEm2 = hpOfMB1 * 2;
	this->damageOfEm3 = damageOfMB1 * 2;
	this->hpOfEm3 = hpOfMB1;
	this->damageOfEm4 = damageOfEm3;
	this->hpOfEm4 = hpOfEm3;
	this->damageOfBoss = 1000.0f;
	this->hpOfBoss = 5000.0f;

	this->damageOfBlueBoss = 400.0f;
	this->hpOfBlueBoss = 3000.0f;
	CCLOG("------- Done Update");

}

void Update::readFile(string path)
{

	bool isExist = FileUtils::getInstance()->isFileExist(path);
	string data = FileUtils::getInstance()->getStringFromFile(path);
	log("%s", data.c_str());
	char* cstr = const_cast<char*>(data.c_str());
	string text;
	string numOfImage;
	char* pch = strtok(cstr, "\r\n");

	while (pch != NULL)
	{
		std::string::size_type sz;
		float dt = std::stof(pch, &sz);
		allData.push_back(dt);
		pch = strtok(NULL, "\r\n");
	}
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

float Update::getDamageOfEm4()
{
	return this->damageOfEm4;
}

float Update::getHPOfEm4()
{
	return this->hpOfEm4;
}

float Update::getDamageOfBoss()
{
	return this->damageOfBoss;
}

float Update::getHPOfBoss()
{
	return this->hpOfBoss;
}

float Update::getDamageOfBlueBoss()
{
	return this->damageOfBlueBoss;
}

float Update::getHPOfBlueBoss()
{
	return this->hpOfBlueBoss;
}

Player* Update::getPlayer()
{
	return player;
}


void Update::setPlayer(Player* player) {
	this->player = player;
}

string Update::getPath()
{
	return this->path;
}

int Update::getSumVillages()
{
	return this->sumVillages;
}

float Update::getStunTime()
{
	return this->stunTime;
}

float Update::getConditionUlti()
{
	return this->conditionUlti;
}

void Update::setSumVillages(int sumVillages)
{
	this->sumVillages = sumVillages;
}

void Update::setHpOfPlayer(float hp)
{
	this->hpOfPlayer = hp;
}

void Update::setDamageOfPlayer(float damage)
{
	this->damageOfPlayer = damage;
}

void Update::setTimeStun(float time)
{
	this->stunTime = time;
}

void Update::setUltiDame(float i)
{
	this->conditionUlti = i;
}

string Update::getPathStateSkill()
{
	return this->pathStateSkill;
}

void Update::readFileStateSkill(string path)
{
	bool isExist = FileUtils::getInstance()->isFileExist(path);
	string data = FileUtils::getInstance()->getStringFromFile(path);
	char* cstr = const_cast<char*>(data.c_str());
	string text;
	string numOfImage;
	char* pch = strtok(cstr, "\r\n");

	while (pch != NULL)
	{
		std::string::size_type sz;
		float dt = std::stoi(pch, &sz);
		states.push_back(dt);
		pch = strtok(NULL, "\r\n");
	}
}

int Update::getStateUlti()
{
	return stateUlti;
}

int Update::getStateSlow()
{
	return stateSlow;
}

void Update::setStateUlti(int i)
{
	this->stateUlti = i;
}

void Update::setStatekSlow(int i)
{
	this->stateSlow = i;
}
