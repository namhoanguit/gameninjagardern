#include "fwAnimation.h"



void fwAnimation::drawCurrentFrame(D3DXVECTOR3 pos, const DrawCenter&	drawCenter,
	D3DXVECTOR2 scale, D3DCOLOR color, D3DXVECTOR2 translate,
	float angle, bool converted)
{
	m_Sprite->drawFrame(pos, m_CurrentIndex, drawCenter, scale, color, translate, angle, converted);
}

int fwAnimation::getFrameWidth(){ return m_Sprite->getFrameWidth(); }

int fwAnimation::getFrameHeight(){ return m_Sprite->getFrameHeight(); }

void fwAnimation::setSprite(fwSprite *sprite){ m_Sprite = sprite; }

void fwAnimation::generateNextIndexHorizontal()
{
	if (((GetTickCount() - m_TimeLine) >= m_TimeToNextSprite))
	{
		m_TimeLine = GetTickCount();
		m_CurrentIndex = (m_CurrentIndex + 1) % m_Sprite->getFramesCount();
	}
}

void fwAnimation::setCurrentIndex(int index)
{
	m_CurrentIndex = index;
}
void fwAnimation::setindex(int tu, int den)
{
	if (((GetTickCount() - m_TimeLine) >= m_TimeToNextSprite))
	{
		m_TimeLine = GetTickCount();
		if (tu == den)
		{
			m_CurrentIndex = tu;
		}
		else
			if (m_CurrentIndex < den)
				m_CurrentIndex++;
			else if (m_CurrentIndex == den)
				m_CurrentIndex = tu;
			else m_CurrentIndex = 0;
		
	}
	
	 
	 
}

fwAnimation::fwAnimation(fwSprite* sprite, DWORD timeToNextSprite)
{
	m_TimeLine = GetTickCount();
	this->setSprite(sprite);
	m_CurrentIndex = 0;
	m_TimeToNextSprite = timeToNextSprite;

}
