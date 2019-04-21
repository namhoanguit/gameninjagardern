#ifndef __FW_CAMERA_H__
#define __FW_CAMERA_H__
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "fwmacro.h"
#include "fwconfig.h"
#include "BoundingBox.h"

class fwCamera
{
private:
	static fwCamera* m_Instance;
	D3DXMATRIX m_Transform;
	D3DXVECTOR3 m_CurrPositionDescartes;
	BoundingBox m_bb;

	fwCamera();
	~fwCamera();
public:
	void update(DWORD deltatime);
	void draw();

	D3DXVECTOR3 getPossition(){ return m_CurrPositionDescartes; }
	void setPossition(D3DXVECTOR3 pos) { m_CurrPositionDescartes = pos; }
	static D3DXMATRIX gettransformCoordinates();

	BoundingBox getBoundingBox(){ return m_bb; }
	static fwCamera* getInstance();
};

#define fwCAMERA_INSTANCE fwCamera::getInstance()
#endif