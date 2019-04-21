#include "Left.h"

#define PATH_MANOBJ "res\\images\\player\\mainobject.png"
#define VELOCITY 200

Left::Left()
{
	m_Id = idPLAYER;
	m_Pos = D3DXVECTOR3(0, 0, 0);

	m_texture = new fwTexture(PATH_MANOBJ);
	m_sprite = new fwSprite(m_texture, D3DXVECTOR3(12, 10, 0), 2, 4, 42, 42);
	m_animation = new fwAnimation(m_sprite, 500);

}

Left::~Left()
{
	delete m_texture, m_sprite, m_animation;
	m_texture = nullptr;
	m_texture = nullptr;
	m_animation = nullptr;
}



void Left::update(DWORD deltatime)
{
	//updateKeyBoard(deltatime);
	updateTime(deltatime);
}



void Left::updateKeyBoard(DWORD deltatime)
{
	if (fwGET_KEY(DIK_UP) == KEY_DOWN || fwGET_KEY(DIK_UP) == KEY_PRESS)m_Pos.y += VELOCITY * 16 / 1000;
	if (fwGET_KEY(DIK_DOWN) == KEY_DOWN || fwGET_KEY(DIK_DOWN) == KEY_PRESS)m_Pos.y -= VELOCITY * 16 / 1000;
	if (fwGET_KEY(DIK_RIGHT) == KEY_DOWN || fwGET_KEY(DIK_RIGHT) == KEY_PRESS)m_Pos.x += VELOCITY * 16 / 1000;
	if (fwGET_KEY(DIK_LEFT) == KEY_DOWN || fwGET_KEY(DIK_LEFT) == KEY_PRESS)m_Pos.x -= VELOCITY * 16 / 1000;
}


void Left::updateTime(DWORD deltatime)
{

	//if (m_Pos.y<=0)m_Pos.y += VELOCITY * 16 / 1000;
	//if (m_Pos.y>0)m_Pos.y -= VELOCITY * 16 / 1000;
	//if (m_Pos.x<=0)m_Pos.x += VELOCITY * 16 / 1000;
	//if (m_Pos.x >0)m_Pos.x -= VELOCITY * 16 / 1000;

	m_Pos.x += VELOCITY * 16 / 1000;
	if (m_Pos.x >200)m_Pos.y -= VELOCITY * 16 / 1000;

}




void Left::updateCollide(SweepAABB sweepaabb, DWORD deltatime)
{
	if (sweepaabb.m_colDirection == eColDirection::TOP);
	if (sweepaabb.m_colDirection == eColDirection::BOT);
	if (sweepaabb.m_colDirection == eColDirection::LEFT);
	if (sweepaabb.m_colDirection == eColDirection::RIGHT);
}

void Left::draw()
{
	m_animation->drawCurrentFrame(m_Pos, BOTTOMLEFT);
	m_animation->generateNextIndexHorizontal();
}