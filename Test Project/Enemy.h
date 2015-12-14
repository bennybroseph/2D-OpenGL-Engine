#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <Collision.h>
#include <GLSprite.h>

#include <time.h>
#include <Windows.h>

class Enemy : public Collision::Object
{
private:
	GLSprite<int>* m_glPlayerSprite;
	Graphics::GLSurface<int>* m_glSurface;

public:
	void Update();
	void LateUpdate();

	//void OnBoxCollision(Object& a_oOther);

	Enemy();
	~Enemy();
};

#endif _ENEMY_H_