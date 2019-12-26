#ifndef _MODEL_H_
#define _MODEL_H_
class Model
{
public:
	static const int BITMASK_WORLD = 100;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;
	static const int BITMASK_GROUND = BITMASK_PLAYER + 1;
};
#endif