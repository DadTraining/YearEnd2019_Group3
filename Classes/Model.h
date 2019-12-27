#ifndef _MODEL_H_
#define _MODEL_H_
class Model
{
public:
	static const int BITMASK_WORLD = 100;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;
	static const int BITMASK_GROUND = BITMASK_PLAYER + 1;
	static const int BITMASK_ENEMY = BITMASK_GROUND + 1;
	static const int BITMASK_VILLAGER = BITMASK_ENEMY + 1;
	static const int MAIN_CHARACTER_TYPE = 1;
	static const int MAIN_MONSTER_TYPE = 2;
	static const int MAIN_VILLAGER_TYPE = 3;

};
#endif