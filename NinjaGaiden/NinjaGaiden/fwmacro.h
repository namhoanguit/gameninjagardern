#ifndef __FW_MACRO_H__
#define __FW_MACRO_H__

#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;

typedef	std::wstring	tstring;
typedef std::wfstream	tfstream;
typedef wchar_t			tchar;
#define PATH_OBJECT1 "res\\txtmaps\\map1.txt"
#define PATH_MAP "res\\images\\map1.png"

#define TRANSLATE_NO		D3DXVECTOR2(0.0f, 0.0f)

#define DEFAULT_DEPTH			0.0f
#define DEFAULT_COLORKEY		D3DCOLOR_XRGB(0,0,0)

// Specify position on screen.
//#define WDPOS_CENTER		(D3DXVECTOR3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT / 2.0F,	DEFAULT_DEPTH))
//#define WDPOS_NOTIFY		(D3DXVECTOR3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT / 4.0F,	DEFAULT_DEPTH))
//#define WDPOS_BOTTOM_CENTER (D3DXVECTOR3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT,			DEFAULT_DEPTH))
//#define WDPOS_BOTTOM_RIGHT	(D3DXVECTOR3(RESOLUTION_WIDTH,			RESOLUTION_HEIGHT,			DEFAULT_DEPTH))
//#define WDPOS_BOTTOM_LEFT	(D3DXVECTOR3(0.0F,						RESOLUTION_HEIGHT,			DEFAULT_DEPTH))
//#define WDPOS_TOP_LEFT		(D3DXVECTOR3(0.0F,						0.0F,						DEFAULT_DEPTH))
//#define WDPOS_CENTER_(A)	(D3DXVECTOR3(RESOLUTION_WIDTH / 2.0F,	100 + 80 * A,				DEFAULT_DEPTH))
//#define POSITION_ZERO		(D3DXVECTOR3(0.0F,						0.0F,						0.0F))

// Colors.
#define COLOR_NO			D3DCOLOR_XRGB(255,	255,	255)
#define COLOR_WHITE			D3DCOLOR_XRGB(255,	255,	255)
#define COLOR_BLACK			D3DCOLOR_XRGB(0,	0,		0)
#define COLOR_RED			D3DCOLOR_XRGB(237,	28,		36)
#define COLOR_YELLOW		D3DCOLOR_XRGB(255,	242,	 0)
#define COLOR_ORANGE		D3DCOLOR_XRGB(255,	127,	39)
#define COLOR_GREEN			D3DCOLOR_XRGB(34,	177,	76)
#define COLOR_BLEND			D3DCOLOR_ARGB(150,	255,	255, 255)
#define COLOR_NBLEND		D3DCOLOR_ARGB(0,	255,	255, 255)

// About zoom macros.
#define SCALE_NO		D3DXVECTOR2(1.0F, 1.0F)		// không lật ảnh
#define SCALE_FLIP_X	D3DXVECTOR2(-1.0F, 1.0F)	// lật ảnh theo trục X
#define SCALE_FLIP_Y	D3DXVECTOR2(1.0F, -1.0F)	// lật ảnh theo trục y
#define SCALE_FLIP_XY	D3DXVECTOR2(-1.0F, -1.0F)
#define SCALE_A(A)		D3DXVECTOR2(A, A)
#define SCALE_XY(A, B)	D3DXVECTOR2(A, B)
#define SCALE_VELO_X(A)	D3DXVECTOR2(A != 0? (float)A/fabs(A) : 1.0F, 1.0F)

#define PI			3.14159265358979323
#define PI_2		(2 * PI)

// About rotate macros.
#define ANGLE_NO					0.0F
#define ANGLE_CLOCKWISE(A)			(-A)
#define ANGLE_COUNTER_CLOCKWISE(A)	A
#define ANGLE_DEGREE_LIM			360
#define DEGREE_TO_RADIAN(A)			((A) * PI / 180.0)
#define RADIAN_TO_DEGREE(A)			((A) * 180.0 / PI)


enum DrawCenter
{
	TOPLEFT = 0,
	TOPRIGHT,
	BOTTOMCENTER,
	CENTER,
	BOTTOMLEFT,
	BOTTOMRIGHT,
	TOPCENTER,
	NUM_OF_DRAWCENTER
};



#define SAFE_RELEASE(A)				{if (A != nullptr) {delete A; A = nullptr;}}
#define SAFE_RELEASE_ARRAY(A)		{if (A != nullptr) {delete[] A; A = nullptr;}}
#define SAFE_DELETE_POINTER(p)       { if(p) { delete (p);     (p)=nullptr; } }
#define SAFE_DELETE_POINTER_ARRAY1(p) { if(p) { delete[] (p);   (p)=nullptr; } }
#define SAFE_DELETE_POINTER_ARRAY2(p,n) {if(p) {FOR_e(n)delete[](p[i]; (p)=nullptr; )}}
#define SAFE_DELETE_POINTER_ARRAY3(p,n,m) {if(p) { }}




// Simple defination For-loop macros.
#define FOR(A)				for(decltype(A) i = 0; i < (A); ++i)
#define FOR_e(A)			for(int i = 0; i < (A); ++i)
#define DFOR(A)				for(int i = (A); i >= 0; --i)
#define FORJ(A)				for(auto j = (A) - (A); j < (A); ++j)
#define FOR_A(start,stop)	for(auto i = start; i != stop; ++i)
#define FOR_AB(A, B)		for(auto i = (A); i < (B); ++i)


#define FORi(A)				for(decltype(A) i = 0; i < (A); i++)

#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL


#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#define WAVEFILE_READ   1
#define WAVEFILE_WRITE  2



#endif 
// __FW_MACRO_H__
