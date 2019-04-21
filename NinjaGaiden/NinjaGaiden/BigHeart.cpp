#include "BigHeart.h"

#define PATH_MANOBJ "res\\images\\item\\1.png"
#define VELOCITY 50

BigHeart::BigHeart()
{
	m_Id = idPLAYER;
	m_Pos = D3DXVECTOR3(100, 100, 0);

	m_texture = new fwTexture(PATH_MANOBJ, D3DCOLOR_XRGB(255, 0, 255));
	m_sprite = new fwSprite(m_texture, D3DXVECTOR3(0, 0, 0), 4, 4, 64, 32);
	m_animation = new fwAnimation(m_sprite, 500);// 500 là thời gian chuyển đổi giữa 2 frame liên tiếp, càng lớn càng chậm

}

BigHeart::~BigHeart()
{
	delete m_texture, m_sprite, m_animation;
	m_texture = nullptr;
	m_texture = nullptr;
	m_animation = nullptr;
}



void BigHeart::update(DWORD deltatime)
{
	//updateKeyBoard(deltatime);
	if (m_Pos.x <= 0)
	{

		m_bb.m_vx = VELOCITY;
	}
	else
	if (m_Pos.x >= 150)
	{

		m_bb.m_vx = -VELOCITY;
	}

	else if (m_bb.m_vx == 0)
	{

		m_bb.m_vx = VELOCITY;

	}

	m_bb.m_pos = m_Pos;
	m_bb.m_height = m_animation->getFrameHeight() - 2;
	m_bb.m_width = m_animation->getFrameWidth() - 2;
}






void BigHeart::updateCollide(SweepAABB col, DWORD deltatime)
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

void BigHeart::draw()
{

	if (m_bb.m_vx<0)
	{
		m_animation->drawCurrentFrame(m_Pos, BOTTOMLEFT, SCALE_NO, D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);

	}
	else
	{
		m_animation->drawCurrentFrame(m_Pos, BOTTOMLEFT, SCALE_FLIP_X, D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);
	}
	m_animation->generateNextIndexHorizontal(); //tự động tính toán sau bao lâu sẽ tự động đến frame kế tiếp.
	//m_bb.m_vx = m_bb.m_vy = 0;
}