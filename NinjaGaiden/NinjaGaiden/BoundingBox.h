#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include <d3d9.h>
#include <d3dx9.h>

#define VECTOR3_ZERO D3DXVECTOR3(0.0f,0.0f,0.0f)

struct BoundingBox
{
	D3DXVECTOR3 m_pos;
	float m_vx, m_vy, m_width, m_height;

	BoundingBox()
	{
		m_pos = VECTOR3_ZERO;
		m_vx = m_vy = m_width = m_height = 0.0f;
	}

	BoundingBox(float xpos, float ypos, float width, float heigh)
	{
		m_vx = m_vy = 0.0f;
		m_pos = D3DXVECTOR3(xpos, ypos, 0.0f);
		m_width = width;
		m_height = heigh;
	}

	BoundingBox(float xpos, float ypos, float width, float heigh, float vx, float vy)
	{
		m_pos = D3DXVECTOR3(xpos, ypos, 0.0f);
		m_width = width;
		m_height = heigh;
		m_vx = vx;
		m_vy = vy;
	}

	void setVelocityBoundingBox(float vx, float vy)
	{
		m_vx = vx;
		m_vy = vy;
	}

	bool compareValue(BoundingBox& bb)
	{
		return (m_pos.x == bb.m_pos.x &&
			m_pos.y == bb.m_pos.y &&
			m_width == bb.m_width &&
			m_height == bb.m_height);
	}
};









#endif