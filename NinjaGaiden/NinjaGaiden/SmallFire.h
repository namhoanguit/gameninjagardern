
#include "StaticObject.h"
#include "Collision.h"


class SmallFire : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	SmallFire();
	~SmallFire();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






