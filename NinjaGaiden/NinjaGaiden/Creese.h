
#include "StaticObject.h"
#include "Collision.h"


class Creese : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	Creese();
	~Creese();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






