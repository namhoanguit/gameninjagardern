#ifndef __FW_ANIMATION_H__
#define __FW_ANIMATION_H__

#include "fwSprite.h"

class fwAnimation
{
private:
	fwSprite *m_Sprite;
	DWORD m_TimeLine;

public:

	int m_CurrentIndex;
	DWORD m_TimeToNextSprite;

	fwAnimation(){}
	fwAnimation(fwSprite* sprite, DWORD timeToNextSprite); //timeToNextSprite thời gian chuyển đổi liên tục giữa 2 frame
	~fwAnimation(){}

	void setSprite(fwSprite *sprite);



	void generateNextIndexHorizontal();


	int getFrameWidth();
	int getFrameHeight();

	DWORD getTimeLine(){ return m_TimeLine; }
	void setindex(int tu,int den);
	void setCurrentIndex(int index);
	void drawCurrentFrame(D3DXVECTOR3 pos,
		const DrawCenter&	drawCenter = DrawCenter::CENTER,
		D3DXVECTOR2			scale = SCALE_NO,
		D3DCOLOR			color = 0xFFFFFFFF,
		D3DXVECTOR2			translate = TRANSLATE_NO,
		float				angle = ANGLE_NO,
		bool				converted = true);
	void drawCurrentFrame_MAP(D3DXVECTOR3 pos,
		const DrawCenter&	drawCenter = DrawCenter::CENTER,
		D3DXVECTOR2			scale = SCALE_NO,
		D3DCOLOR			color = 0xFFFFFFFF,
		D3DXVECTOR2			translate = TRANSLATE_NO,
		float				angle = ANGLE_NO,
		bool				converted = true);
};
#endif // __FW_ANIMATION_H__
