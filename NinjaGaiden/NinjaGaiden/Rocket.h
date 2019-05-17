

#include "DynamicObject.h"
#include "fwAnimation.h"
#include "fwKeyboard.h"
#include "Collision.h"


class Rocket : public DynamicObject
{
	fwAnimation* m_animation;
	fwTexture* m_texture;
	fwSprite* m_sprite;

public:
	Rocket();
	~Rocket();

	void update(DWORD deltatime);


	void updateTime(DWORD deltatime);
	void updateCollide(SweepAABB, DWORD deltatime = 16);

		void draw();
};






