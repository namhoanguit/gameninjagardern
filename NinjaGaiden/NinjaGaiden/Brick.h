
#include "StaticObject.h"
#include "Collision.h"


class Brick : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	Brick();
	~Brick();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






