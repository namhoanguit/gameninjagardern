
#include "StaticObject.h"
#include "Collision.h"


class Whip : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	Whip();
	~Whip();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






