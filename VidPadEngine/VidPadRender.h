#pragma once
#include "VidPadMedia.h"
#include "VidPadDecoder.h"
#include "VidPadList.h"
#include <vector>
#include <Windows.h>
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#define VIDPAD_API __declspec(dllimport)
#endif

using namespace std;

class VIDPAD_API VidPadRender
{
public:
	VidPadRender();
	~VidPadRender();
	void ChangeBackColor(float r,float g,float b,float a);
	void RenderNextFrame(VidPadList *List);
	VidPadMedia *BackgroundImage;
	VidPadMedia *ForeGroundImage;
	void SetCtrl(bool State);
	bool GetCtrl();
	void SetAlt(bool State);
	bool GetAlt();
	bool RenderBack, RenderFore;
	int fps;
private :
	Color DefColor;
	bool CtrlState;
	bool AltState;
	//VidPadEffect *BackgroundEffect;
};

