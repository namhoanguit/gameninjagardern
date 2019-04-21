
#include "StaticObject.h"
#include "Collision.h"


class BigFire : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	BigFire();
	~BigFire();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






