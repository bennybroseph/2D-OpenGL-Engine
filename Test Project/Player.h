#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Object.h"

class Player : protected Object<int>
{
private:

public:
	void Update();
	void LateUpdate();

	Player();
	~Player();
};

#endif // _PLAYER_H_

