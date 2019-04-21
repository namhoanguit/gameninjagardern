#ifndef __FW_SPRITE_H__
#define __FW_SPRITE_H__

#include "fwTexture.h"

class fwSprite
{	 
protected:
	fwTexture *m_Texture;

	D3DXVECTOR3 m_PosInTexture;
	int m_FramesPerRow;		// số frame trên 1 dòng
	int m_FramesCount;	// đến số frame
	int m_FrameWidth;
	int m_FrameHeight;
public:
	fwSprite() {};
	fwSprite(fwTexture*);
	fwSprite(fwTexture *texture, D3DXVECTOR3 posintexture,
		int framesperrow, int framescount, int framewidth, int frameheight);

	void setSprite(fwTexture *texture, D3DXVECTOR3 posintexture,
		int framesperrow, int framescount, int framewidth, int frameheight);

	void setPosInTexture(D3DXVECTOR3&);
	void setSizeFrame(int FrameWidth, int FrameHeight);

	~fwSprite();

	int getFramesPerRow();
	int getFramesCount();
	int getFrameWidth();
	int getFrameHeight();

	void drawFrame(D3DXVECTOR3 pos,
		int					frameIndex = 0,
		const DrawCenter&	drawCenter = DrawCenter::BOTTOMLEFT,
		D3DXVECTOR2			scale = SCALE_NO,
		D3DCOLOR			color = 0xFFFFFFFF,
		D3DXVECTOR2			translate = TRANSLATE_NO,
		float				angle = ANGLE_NO,
		bool				converted = true);

	


	// -----------------------------------------------------------------------------
	//Name: Texture
	//Desc: Methods involve Texture
	fwTexture *getTexture();
	D3DXVECTOR2 getPosInTexture();
	void loadTexture(fwTexture *texture);
	void loadTexture(fwTexture *texture, D3DXVECTOR3 posintexture,
		int frameperrow, int framecount, int framewidth, int frameheight);
	// -----------------------------------------------------------------------------
};

#endif // __FW_SPRITE_H__
