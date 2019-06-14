#include "fwCamera.h"

fwCamera *fwCamera::m_Instance = nullptr;

fwCamera::fwCamera()
{
	m_CurrPositionDescartes = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixIdentity(&m_Transform);
	m_bb.m_height = RESOLUTION_HEIGHT * 3;
	m_bb.m_width = RESOLUTION_WIDTH * 3 /*+ 150*/;
}

fwCamera::~fwCamera(){ SAFE_DELETE_POINTER(m_Instance); }

fwCamera* fwCamera::getInstance()
{
	if (m_Instance == nullptr)m_Instance = new fwCamera();
	return m_Instance;
}

D3DXMATRIX fwCamera::gettransformCoordinates()
{
	D3DXMATRIX mtScale;
	D3DXMatrixScaling(&mtScale, 1, -1, 0);

	D3DXMATRIX mtTrans;
	D3DXMatrixTranslation(&mtTrans, -((int)fwCamera::getInstance()->m_CurrPositionDescartes.x /*- 10*/),
		-((int)fwCamera::getInstance()->m_CurrPositionDescartes.y + RESOLUTION_HEIGHT),
		/*(int)fwCamera::getInstance()->m_CurrPositionDescartes.z*/0);

	fwCamera::getInstance()->m_Transform = mtTrans * mtScale;

	return fwCamera::getInstance()->m_Transform;
}

void fwCamera::update(DWORD deltatime)
{
	//m_bb.m_pos.x = m_CurrPositionDescartes.x - RESOLUTION_WIDTH;
	 
	//m_bb.m_pos.y = ((int)(m_CurrPositionDescartes.y / RESOLUTION_HEIGHT) - 1)*RESOLUTION_HEIGHT +
	//	(RESOLUTION_HEIGHT - ((int)m_CurrPositionDescartes.y) % RESOLUTION_HEIGHT - m_bb.m_height);
	 
	m_bb.m_pos.x = m_CurrPositionDescartes.x;
	m_bb.m_pos.y = m_CurrPositionDescartes.y;
}

