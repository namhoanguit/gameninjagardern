
#include "StaticObject.h"
#include "Collision.h"


class Gate2 : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	Gate2();
	~Gate2();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






