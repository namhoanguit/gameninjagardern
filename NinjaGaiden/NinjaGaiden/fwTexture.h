#ifndef __FW_TEXTURE_H__
#define __FW_TEXTURE_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "fwmacro.h"
#include "BoundingBox.h"

class fwTexture
{
protected:
	static LPD3DXSPRITE			m_Sprite_Handler;
	static D3DXMATRIX			m_cameraConvertMatrix;
	static LPDIRECT3DDEVICE9	m_d3dDevice;

	static LPD3DXLINE m_Line;


	char				*m_path;
	D3DXIMAGE_INFO		*m_info;
	LPDIRECT3DTEXTURE9	*m_texture;
	D3DCOLOR			m_ColorKey;

	D3DXVECTOR3 computeCenter(const DrawCenter& drawCenter, RECT *scrRect);

	void		transformImage(const float& angle,
		const D3DXVECTOR2& scale,
		const D3DXVECTOR2& translate,
		const D3DXVECTOR3& position,
		const D3DMATRIX& originalStatus);

	void		releaseTexture();

	virtual void loadImage();

public:
	fwTexture(){};
	~fwTexture();
	fwTexture(const char* _path, D3DCOLOR _colorKey = DEFAULT_COLORKEY);

	static HRESULT	initHandler(const LPD3DXSPRITE& _handler);
	static HRESULT	releaseHandler();
	bool			isLoaded()		const;

	LPD3DXSPRITE	getHandler()	const;
	char*			getPath()		const;
	D3DXIMAGE_INFO	getInfo()		const;

	D3DXVECTOR2 getFrameSize();

	void drawImage(D3DXVECTOR3			pos = D3DXVECTOR3(0, 0, 0.5),
		RECT*				srcRect = 0,
		const DrawCenter&	drawCenter = DrawCenter::BOTTOMLEFT,
		D3DCOLOR			color = 0xFFFFFFFF,
		D3DXVECTOR2			scale = SCALE_NO,
		D3DXVECTOR2			translate = TRANSLATE_NO,
		float				angle = ANGLE_NO,
		bool				converted = true);

	void drawImage(D3DXVECTOR3			pos,
		RECT*				srcRect,
		D3DXVECTOR3			drawCenter,
		D3DCOLOR			color = 0xFFFFFFFF,
		D3DXVECTOR2			scale = SCALE_NO,
		D3DXVECTOR2			translate = TRANSLATE_NO,
		float				angle = ANGLE_NO,
		bool				converted = true);

	static void		setPositioncConvertMatrix(const D3DXMATRIX& _newMatrix);

	static void drawBoundingBox(BoundingBox& bb, D3DCOLOR color = 0xFFFFFFFF);
};

#define BOUNDINGBOX_DRAW(A,B) fwTexture::drawBoundingBox(A,B)

#endif // __FW_Texture_H__
