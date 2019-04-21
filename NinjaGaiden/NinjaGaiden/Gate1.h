
#include "StaticObject.h"
#include "Collision.h"


class Gate1 : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	Gate1();
	~Gate1();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






