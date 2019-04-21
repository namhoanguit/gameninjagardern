
#include "StaticObject.h"
#include "Collision.h"


class Door1 : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	Door1();
	~Door1();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






