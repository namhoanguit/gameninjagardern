

#include "DynamicObject.h"
#include "fwAnimation.h"
#include "fwKeyboard.h"
#include "Collision.h"


class Bat : public DynamicObject
{
	fwAnimation* m_animation;
	fwTexture* m_texture;
	fwSprite* m_sprite;

public:
	Bat();
	~Bat();

	void update(DWORD deltatime);

	void Going(DWORD deltatime);

	void updateKeyBoard(DWORD deltatime);
	void updateCollide(SweepAABB, DWORD deltatime = 16);


	void draw();
};






