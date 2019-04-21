
#include "StaticObject.h"
#include "Collision.h"


class Door2 : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	Door2();
	~Door2();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






