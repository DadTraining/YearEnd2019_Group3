#ifndef _MODEL_H_
#define _MODEL_H_
#define TAG_ANIMATE_RUN 111
#define TAG_ANIMATE_IDLE1 121
#define TAG_ANIMATE_IDLE2 122
#define TAG_ANIMATE_ATTACK 131
#define TAG_ENEMY_ATTACK TAG_ANIMATE_ATTACK + 1
#define SPEED 5.0f
#define m_SCALE 4.0f
class Model
{
public:
	static const int BITMASK_WORLD = 100;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;
	static const int BITMASK_GROUND = BITMASK_PLAYER + 1;
	static const int BITMASK_ENEMY = BITMASK_GROUND + 1;
	static const int BITMASK_VILLAGER = BITMASK_ENEMY + 1;
	static const int BITMASK_NORMAL_ATTACK = 50;
	static const int BITMASK_ENEMY1_ATTACK = BITMASK_NORMAL_ATTACK + 10;

	static const int MAIN_CHARACTER_TYPE = 1;
	static const int MAIN_MONSTER_TYPE = 2;
	static const int MAIN_VILLAGER_TYPE = 3;

};
#endif