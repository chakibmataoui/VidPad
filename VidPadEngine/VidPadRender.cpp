#include "stdafx.h"
#include "VidPadRender.h"


VidPadRender::VidPadRender()
{
	//DEFINE DEFAULT COLOR
	DefColor.r = 0.0;
	DefColor.g = 0.0;
	DefColor.b = 0.0;
	DefColor.a = 0.0;
	BackgroundImage = new VidPadMedia();
	ForeGroundImage = new VidPadMedia();
	CtrlState = false;
	AltState = false;
	RenderBack = false;
	RenderFore = false;
	fps = 29.97;
}


VidPadRender::~VidPadRender()
{
	BackgroundImage->~VidPadMedia();
	ForeGroundImage->~VidPadMedia();
}
void VidPadRender::ChangeBackColor(float r, float g, float b,float a)
{
	//CHANGE BACKGROUND COLOR
	DefColor.r = r;
	DefColor.g = g;
	DefColor.b = b;
	DefColor.a = a; 
}
void VidPadRender::RenderNextFrame(VidPadList *List)
{
	//TODO ADD RENDERING FOR DIFFERENT MEDIA TYPES AS IMAGE/VIDEO AND COLOR OR RECT COLOR
	glClearColor(DefColor.r, DefColor.g, DefColor.b, DefColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	if (RenderBack)
	{
		List->BackgroundBuffer->RenderFrame();
	}
	BackgroundImage->RenderFrame();
	for (unsigned int i = 0; i < List->KeyList.size(); i++)
	{
		List->MediaList[List->KeyList[i]]->RenderFrame();

	}
	ForeGroundImage->RenderFrame();
	if (RenderFore)
	{
		List->Foregroundbuffer->RenderFrame();
	}
	//glDrawPixels(1366,789,GL_RGBA,GL_UNSIGNED_BYTE,FrameBuffer);
}
void VidPadRender::SetCtrl(bool State)
{
	CtrlState = State;
}
bool VidPadRender::GetCtrl()
{
	return CtrlState;
}
void VidPadRender::SetAlt(bool State)
{
	AltState = State;
}
bool VidPadRender::GetAlt()
{
	return AltState;
}