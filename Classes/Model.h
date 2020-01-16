#ifndef _MODEL_H_
#define _MODEL_H_
#define TAG_ANIMATE_RUN 111
#define TAG_ANIMATE_IDLE1 121
#define TAG_ANIMATE_IDLE2 122
#define TAG_ANIMATE_HIT TAG_ANIMATE_IDLE2 + 1
#define TAG_ANIMATE_ATTACK 131
#define TAG_ANIMATE_DIE TAG_ANIMATE_ATTACK + 1
#define TAG_ATTACK TAG_ANIMATE_DIE + 1
#define TAG_ANIMATE_FREEZER TAG_ATTACK + 1
#define m_SCALE_32x32 4.0f
#define m_SCALE_16x16 m_SCALE_32x32 / 2
#define TAG_ENEMY_ATTACK TAG_ANIMATE_ATTACK + 1
#define SPEED_PLAYER 5.0f
#define SPEED_MB01 0.6f
#define TIME_MOVE_TO_PLAYER 10
#define VISION_OF_MB 400
#define VISION_OF_EM2 300
#define VISION_OF_EM3 600
#define RANGE_OF_MB 100
#define VISION_OF_EM4 300
#define VISION_OF_KNIGHT 600
#define RANGE_OF_KNIGHT 300
#define TIME_ONE_ATTACK 0.1f
#define TIME_ONE_HIT 0.1f
#define TIME_ONE_IDLE 0.2f
#define TIME_ONE_RUN 0.1f
#define TIME_ONE_DEAD 0.26f
#define TIME_ONE_WALK 0.1f
#include<Player.h>
class Model
{
public:
	static const int BITMASK_WORLD = 1;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;
	static const int BITMASK_GROUND = BITMASK_PLAYER + 1;
	static const int BITMASK_ENEMY = BITMASK_GROUND + 1;
	static const int BITMASK_VILLAGER = BITMASK_ENEMY + 1;
	static const int BITMASK_ENEMY2 = BITMASK_VILLAGER + 1;
	static const int BITMASK_ENEMY3 = BITMASK_ENEMY2 + 1;
	static const int BITMASK_BOSS = BITMASK_ENEMY3 + 1;
	static const int BITMASK_ENEMY4 = BITMASK_BOSS + 1;
	static const int BITMASK_BLUEBOSS = BITMASK_ENEMY4 + 1;
	static const int BITMASK_KNIGHTBOSS = BITMASK_BLUEBOSS + 1;

	static const int BITMASK_NORMAL_ATTACK = 50;
	static const int BITMASK_ENEMY1_ATTACK = BITMASK_NORMAL_ATTACK + 1;
	static const int BITMASK_ENEMY2_ATTACK = BITMASK_ENEMY1_ATTACK + 1;
	static const int BITMASK_ENEMY3_ATTACK = BITMASK_ENEMY2_ATTACK + 1;
	static const int BITMASK_BOSS_ATTACK = BITMASK_ENEMY3_ATTACK + 1;
	static const int BITMASK_ENEMY4_ATTACK = BITMASK_BOSS_ATTACK + 1;
	static const int BITMASK_BLUEBOSS_ATTACK = BITMASK_ENEMY4_ATTACK + 1;
	static const int BITMASK_KNIGHT_ATTACK = BITMASK_BLUEBOSS_ATTACK + 1;

	static const int BITMASK_PORTAL_FINALBOSS = BITMASK_PLAYER + 99;
	static const int BITMASK_PORTAL_ICEBOSS = BITMASK_PORTAL_FINALBOSS + 1;
	static const int BITMASK_PORTAL_LAVABOSS = BITMASK_PORTAL_ICEBOSS + 1;
	static const int BITMASK_PORTAL_BASE = BITMASK_PORTAL_LAVABOSS + 1;

	static const int MAIN_CHARACTER_TYPE = 1;
	static const int MAIN_MONSTER_TYPE = 2;
	static const int MAIN_VILLAGER_TYPE = 3;
	static const int MAIN_ENEMY2_TYPE = 4;
	static const int MAIN_ENEMY3_TYPE = 5;	
	static const int MAIN_BOSS_TYPE = 6;
	static const int MAIN_ENEMY4_TYPE = 7;
	static const int MAIN_BLUEBOSS_TYPE = 8;
	static const int MAIN_KNIGHTBOSS_TYPE = 9;
	static const int FINAL_BOSS_PORTAL_TYPE = 99;
	static const int ICE_BOSS_PORTAL_TYPE = FINAL_BOSS_PORTAL_TYPE + 1;
	static const int LAVA_BOSS_PORTAL_TYPE = ICE_BOSS_PORTAL_TYPE + 1;
	static const int BASE_PORTAL_TYPE = LAVA_BOSS_PORTAL_TYPE + 1;

	static const int KNOCKBACK = 2;
	// Order of the map
	static const int TREE_ORDER = 3;
};
#endif