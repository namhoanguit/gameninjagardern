#include "fwTexture.h"
#include <string.h>


LPD3DXSPRITE		fwTexture::m_Sprite_Handler = 0;
D3DXMATRIX			fwTexture::m_cameraConvertMatrix;
LPDIRECT3DDEVICE9	fwTexture::m_d3dDevice = 0;
LPD3DXLINE			fwTexture::m_Line = nullptr;

// -----------------------------------------------
// Name: fwTexture:initializeHandler()
// Desc: Initialize basic properties to use this class.
// -----------------------------------------------
HRESULT fwTexture::initHandler(const LPD3DXSPRITE& _handler)
{
	HRESULT result;

	fwTexture::m_Sprite_Handler = _handler;
	result = (m_Sprite_Handler == 0);
	result = result | fwTexture::m_Sprite_Handler->GetDevice(&m_d3dDevice);
	D3DXCreateLine(m_d3dDevice, &m_Line);

	return result;
}


// -----------------------------------------------
// Name: fwTexture:releaseHandler()
// Desc: Release it's properties after use (close Game).
// -----------------------------------------------
HRESULT fwTexture::releaseHandler()
{
	if (m_d3dDevice != 0)
		return m_d3dDevice->Release();

	return S_OK;
}


// -----------------------------------------------
// Name: fwTexture:fwTexture()
// Desc: Get the basic info, ready to load.
// -----------------------------------------------
fwTexture::fwTexture(const char* _path, D3DCOLOR _colorKey)
{
	SAFE_RELEASE_ARRAY(m_path);
	m_path = new char[strlen(_path) + 1];
	strcpy(m_path, _path);
	this->m_info = nullptr;

	m_ColorKey = _colorKey;
	loadImage();
}



// -----------------------------------------------
// Name: fwTexture:~fwTexture()
// Desc: Wipe out information to destroy.
// -----------------------------------------------
fwTexture::~fwTexture(void)
{
	SAFE_RELEASE_ARRAY(m_path);
	m_info = nullptr;
	m_texture = nullptr;
}


// -----------------------------------------------
// Name: fwTexture:getHandler()
// Desc: Return handler handling this fwTexture,
// -----------------------------------------------
LPD3DXSPRITE fwTexture::getHandler() const
{
	return fwTexture::m_Sprite_Handler;
}


// -----------------------------------------------
// Name: fwTexture:getName()
// Desc: Return it's path.
// -----------------------------------------------
char* fwTexture::getPath() const
{
	return this->m_path;
}


// -----------------------------------------------
// Name: fwTexture:getInfo()
// Desc: Return the loaded image info.
// -----------------------------------------------
D3DXIMAGE_INFO fwTexture::getInfo() const
{

	return *this->m_info;
}

// -----------------------------------------------
// Name: T6_fwTexture:getFrameSize()
// Desc: Return the loaded image frame size (override by T6_Sprite).
// -----------------------------------------------
D3DXVECTOR2 fwTexture::getFrameSize()
{
	if (!isLoaded())
		loadImage();

	return D3DXVECTOR2(this->m_info->Width, this->m_info->Height);
}

// -----------------------------------------------
// Name: fwTexture:isLoaded()
// Desc: Check if the fwTexture is loaded.
// -----------------------------------------------
bool fwTexture::isLoaded() const
{
	return (m_texture != 0 && m_info != nullptr);
}


// -----------------------------------------------
// Name: fwTexture:loadImageFromStoredInfo()
// Desc: Load image stored in path.
// -----------------------------------------------
void fwTexture::loadImage()
{
	m_texture = new LPDIRECT3DTEXTURE9();
	m_info = new D3DXIMAGE_INFO();
	HRESULT result = D3DXGetImageInfoFromFile(m_path, m_info);

	if (FAILED(result)) {
		return;
	}

	result = D3DXCreateTextureFromFileEx(m_d3dDevice,
		m_path,
		m_info->Width,
		m_info->Height,
		D3DX_FROM_FILE, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		m_ColorKey, m_info, 0,
		m_texture);

	if (FAILED(result)) {
		return;
	}
}

// -----------------------------------------------
// Name: fwTexture:computeCenter()
// Desc: Return the center point of the "current frame" base on draw center (the center point in the human word).
//		 Computing on machine axis(es).
// -----------------------------------------------
D3DXVECTOR3 fwTexture::computeCenter(const DrawCenter& drawCenter, RECT *scrRect)
{
	float _witdth = scrRect->right - scrRect->left;
	float _height = scrRect->bottom - scrRect->top;

	if (drawCenter == DrawCenter::TOPLEFT)	return D3DXVECTOR3(0.0F, 0.0F, DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::BOTTOMLEFT)	return D3DXVECTOR3(0.0F, _height, DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::TOPCENTER)	return D3DXVECTOR3((int)(_witdth / 2.0F), 0.0F, DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::TOPRIGHT)	return D3DXVECTOR3(_witdth, 0.0F, DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::CENTER)	return D3DXVECTOR3((int)(_witdth / 2.0F), (int)(_height / 2.0F), DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::BOTTOMCENTER)	return D3DXVECTOR3((int)(_witdth / 2.0F), _height, DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::BOTTOMRIGHT)	return D3DXVECTOR3(_witdth, _height, DEFAULT_DEPTH);
	else return D3DXVECTOR3(0.0f, 0.0f, DEFAULT_DEPTH);//TOPLEFT
}


// -----------------------------------------------
// Name: fwTexture:transformImage()
// Desc: Scale, rotate and translate image follow passed variables.
// -----------------------------------------------
void fwTexture::transformImage(const float& angle, const D3DXVECTOR2& scale, const D3DXVECTOR2& translate,
	const D3DXVECTOR3& drawCenter, const D3DMATRIX& originalStatus)
{
	if (angle != ANGLE_NO || scale != SCALE_NO || translate != TRANSLATE_NO)
	{
		D3DXVECTOR2 center = (D3DXVECTOR2)drawCenter;
		//D3DXVECTOR2 tran = D3DXVECTOR2(0, 0);

		D3DXMATRIX newStatus;
		D3DXMatrixTransformation2D(&newStatus, &center, 0, &scale,
			&center, D3DXToRadian(angle), &translate);

		// compute and transform the image to current status.
		D3DXMATRIX finalMt = newStatus * originalStatus;
		this->m_Sprite_Handler->SetTransform(&finalMt);
	}
}


// -----------------------------------------------
// Name: fwTexture:drawImage()
// Desc: Draw the defined range of image onto screen.
// -----------------------------------------------
void fwTexture::drawImage(D3DXVECTOR3 pos, RECT* srcRect, const DrawCenter& drawCenter, D3DCOLOR color,
	D3DXVECTOR2 scale, D3DXVECTOR2 translate, float angle, bool converted)
{
	if (m_texture == 0)loadImage();

	//D3DXVECTOR3 center = computeCenter(drawCenter);
	D3DXVECTOR3 center = computeCenter(drawCenter, srcRect);


	this->drawImage(pos, srcRect, center, color, scale, translate, angle, converted);
}


void fwTexture::drawImage(D3DXVECTOR3 pos /*vị trí hiển thị lên màn hình*/, RECT* srcRect /*toạ đô, vị trí, width,height muốn vẽ*/,
	D3DXVECTOR3 drawCenter /*tâm ảnh, sẽ từ tâm ảnh vẽ lên*/, D3DCOLOR color /*màu*/,
	D3DXVECTOR2 scale /*lật ảnh*/, D3DXVECTOR2 translate /*= TRANSLATE_NO*/,
	float angle /*Gốc quay*/,
	bool converted /*= true*/)
{
	if (m_texture == 0)loadImage();


	if (converted)
	{
		D3DXVec3TransformCoord(&pos, &pos, &m_cameraConvertMatrix);

		/*D3DXVECTOR4 postranform;
		D3DXVec3Transform(&postranform, &pos, &m_cameraConvertMatrix);
		pos.x = postranform.x;
		pos.y = postranform.y;*/

	}


	// get image original status.
	D3DXMATRIX oldMt, newMt;
	this->m_Sprite_Handler->GetTransform(&oldMt);
	this->m_Sprite_Handler->GetTransform(&newMt);

	transformImage(angle, scale, translate, pos, newMt);

	pos.x = (float)(int)pos.x;
	pos.y = (float)(int)pos.y;

	m_Sprite_Handler->Draw(*m_texture, srcRect, &drawCenter, &pos, color);
	// set image back to original status.
	m_Sprite_Handler->SetTransform(&oldMt);
}


// -----------------------------------------------
// Name: fwTexture:setPositioncConvertMatrix()
// Desc: Set new matrix to convert draw position.
// -----------------------------------------------
void fwTexture::setPositioncConvertMatrix(const D3DXMATRIX& newMatrix)
{
	fwTexture::m_cameraConvertMatrix = newMatrix;
}


void fwTexture::releaseTexture()
{
	SAFE_RELEASE(m_info);
	SAFE_RELEASE(m_texture);
}

void fwTexture::drawBoundingBox(BoundingBox& bb, D3DCOLOR color)
{
	D3DXVECTOR2 rec[] = { bb.m_pos,
		D3DXVECTOR2(bb.m_pos.x + bb.m_width, bb.m_pos.y),
		D3DXVECTOR2(bb.m_pos.x + bb.m_width, bb.m_pos.y + bb.m_height),
		D3DXVECTOR2(bb.m_pos.x, bb.m_pos.y + bb.m_height),
		bb.m_pos
	};

	D3DXVec2TransformCoord(&rec[0], &rec[0], &m_cameraConvertMatrix);
	D3DXVec2TransformCoord(&rec[1], &rec[1], &m_cameraConvertMatrix);
	D3DXVec2TransformCoord(&rec[2], &rec[2], &m_cameraConvertMatrix);
	D3DXVec2TransformCoord(&rec[3], &rec[3], &m_cameraConvertMatrix);
	D3DXVec2TransformCoord(&rec[4], &rec[4], &m_cameraConvertMatrix);

	m_Line->Draw(rec, 5, color);

}


 