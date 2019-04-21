#include "fwSprite.h"



fwSprite::fwSprite(fwTexture *texture, D3DXVECTOR3 posintexture,
	int framesperrow, int framescount, int framewidth, int frameheight)
{
	loadTexture(texture, posintexture, framesperrow, framescount, framewidth, frameheight);
}
void fwSprite::setSprite(fwTexture *texture, D3DXVECTOR3 posintexture,
	int framesperrow, int framescount, int framewidth, int frameheight)
{
	loadTexture(texture, posintexture, framesperrow, framescount, framewidth, frameheight);
}

fwSprite::fwSprite(fwTexture *texture){ loadTexture(texture); }

fwSprite::~fwSprite(){ delete m_Texture; m_Texture = nullptr;/*Error?*/ }

fwTexture* fwSprite::getTexture(){ return m_Texture; }

D3DXVECTOR2 fwSprite::getPosInTexture(){ return m_PosInTexture; }

void fwSprite::loadTexture(fwTexture *texture)
{
	loadTexture(texture, D3DXVECTOR3(0, 0, 0), 1, 1, texture->getInfo().Width, texture->getInfo().Height);

}

void fwSprite::loadTexture(fwTexture *texture, D3DXVECTOR3 posintexture,
	int framesperrow, int framescount, int framewidth, int frameheight)
{
	m_Texture = texture;
	m_PosInTexture = posintexture;
	m_FramesPerRow = framesperrow;
	m_FramesCount = framescount;
	m_FrameWidth = framewidth;
	m_FrameHeight = frameheight;
}


int fwSprite::getFramesPerRow() { return m_FramesPerRow; }
int fwSprite::getFramesCount()  { return m_FramesCount; }
int fwSprite::getFrameWidth()   { return m_FrameWidth; }
int fwSprite::getFrameHeight()  { return m_FrameHeight; }

void fwSprite::drawFrame(D3DXVECTOR3 pos, int frameIndex, const DrawCenter&	drawCenter,
	D3DXVECTOR2 scale, D3DCOLOR color, D3DXVECTOR2 translate, float angle, bool converted)
{
	RECT srect;

	srect.left = (frameIndex % m_FramesPerRow)*(m_FrameWidth)+m_PosInTexture.x;
	srect.top = (frameIndex / m_FramesPerRow)*(m_FrameHeight)+m_PosInTexture.y;
	srect.right = srect.left + m_FrameWidth;
	srect.bottom = srect.top + m_FrameHeight;

	m_Texture->drawImage(pos, &srect, drawCenter, color, scale, translate, angle, converted);
}



void fwSprite::setPosInTexture(D3DXVECTOR3& pos)
{
	m_PosInTexture = pos;
	m_FramesCount = m_FramesPerRow = 1;
}

void fwSprite::setSizeFrame(int FrameWidth, int FrameHeight)
{
	m_FrameWidth = FrameWidth;
	m_FrameHeight = FrameHeight;
}
