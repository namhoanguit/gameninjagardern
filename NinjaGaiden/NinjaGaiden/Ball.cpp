#include "Ball.h"

#define PATH_Ball "res\\images\\item\\ball.png"
#define VELOCITY 50

Ball::Ball()
{
	m_Id = idENEMY;
	m_Pos = D3DXVECTOR3(200, 200, 0);

	m_texture = new fwTexture(PATH_Ball, D3DCOLOR_XRGB(255,255,255));
	m_sprite = new fwSprite(m_texture, D3DXVECTOR3(0, 0, 0), 4, 4, 32, 32);
	m_animation = new fwAnimation(m_sprite, 500);// 500 là thời gian chuyển đổi giữa 2 frame liên tiếp, càng lớn càng chậm

}

Ball::~Ball()
{
	delete m_texture, m_sprite, m_animation;
	m_texture = nullptr;
	m_texture = nullptr;
	m_animation = nullptr;
}



void Ball::update(DWORD deltatime)
{
	m_bb.m_pos = m_Pos;
	m_bb.m_height = m_animation->getFrameHeight() - 2;
	m_bb.m_width = m_animation->getFrameWidth() - 2;
}






void Ball::updateCollide(SweepAABB col, DWORD deltatime)
{
	float colTime = 1.0f;

	colTime = col.m_colTime;


	if (col.m_colDirection == eColDirection::TOP)
	{
		m_Pos.y += m_bb.m_vy*colTime*deltatime / 1000;
		m_bb.m_vy = 0;
		return;
	}

	if (col.m_colDirection == eColDirection::BOT)
	{
		m_Pos.y += m_bb.m_vy*colTime*deltatime / 1000;
		m_bb.m_vy = 0;
		return;
	}

	if (col.m_colDirection == eColDirection::LEFT)
	{
		m_Pos.x += m_bb.m_vx*colTime*deltatime / 1000;
		m_bb.m_vx = 0;
		return;
	}

	if (col.m_colDirection == eColDirection::RIGHT)
	{
		m_Pos.x += m_bb.m_vx*colTime*deltatime / 1000;
		m_bb.m_vx = 0;
		return;
	}

	m_Pos.x += m_bb.m_vx*colTime*deltatime / 1000;
	m_Pos.y += m_bb.m_vy*colTime*deltatime / 1000;
}

void Ball::draw()
{
	 
	m_animation->drawCurrentFrame(m_Pos, CENTER, SCALE_A(1), D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);
}