#include "EnergyWater.h"

#define PATH_MANOBJ "res\\images\\item\\9.png"

EnergyWater::EnergyWater()
{
	m_Id = idPLAYER;
	m_Pos = D3DXVECTOR3(100, 100, 0);

	m_texture = new fwTexture(PATH_MANOBJ, D3DCOLOR_XRGB(255, 0, 255));
	m_sprite = new fwSprite(m_texture, D3DXVECTOR3(0, 0, 0), 1, 1, 32, 26);
	//obj_static = new StaticObject();// 500 là thời gian chuyển đổi giữa 2 frame liên tiếp, càng lớn càng chậm

}

EnergyWater::~EnergyWater()
{
	delete m_texture, m_sprite;
	m_texture = nullptr;
	m_texture = nullptr;
}




void EnergyWater::updateCollide(SweepAABB col, DWORD deltatime)
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

void EnergyWater::draw()
{
	m_sprite->drawFrame(m_Pos, 0, BOTTOMLEFT, SCALE_NO, D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);

}