#include "BanShee.h"

#define PATH_MANOBJ "res\\images\\enemy\\banshee.bmp"
#define VELOCITY 50

BanShee::BanShee()
{
	m_Id = idPLAYER;
	m_Pos = D3DXVECTOR3(100, 0, 0);

	m_texture = new fwTexture(PATH_MANOBJ);
	m_sprite = new fwSprite(m_texture, D3DXVECTOR3(0, 0, 0), 4, 4, 33, 43);
	m_animation = new fwAnimation(m_sprite, 500);// 500 là thời gian chuyển đổi giữa 2 frame liên tiếp, càng lớn càng chậm

}

BanShee::~BanShee()
{
	delete m_texture, m_sprite, m_animation;
	m_texture = nullptr;
	m_texture = nullptr;
	m_animation = nullptr;
}



void BanShee::update(DWORD deltatime)
{
	//updateKeyBoard(deltatime);
	updateTime(deltatime);
}


void BanShee::updateTime(DWORD deltatime)
{
	if (m_Pos.x >= 100)
	{
		m_Pos.x += VELOCITY * 16 / 1000;
	}
	else
	if (m_Pos.x >= 200)
	{
		m_Pos.x -= VELOCITY * 16 / 1000;
	}
	 

}



void BanShee::updateCollide(SweepAABB col, DWORD deltatime)
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

void BanShee::draw()
{

	if (m_Pos.x>0)
	{
		
		m_animation->drawCurrentFrame(m_Pos, BOTTOMLEFT, SCALE_A(1), D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);
		
	}
	else
	{
		m_animation->drawCurrentFrame(m_Pos, BOTTOMLEFT, SCALE_XY(-1, 1), D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);
	}
	m_animation->generateNextIndexHorizontal(); //tự động tính toán sau bao lâu sẽ tự động đến frame kế tiếp.
	//m_bb.m_vx = m_bb.m_vy = 0;
}