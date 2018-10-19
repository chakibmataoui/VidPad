#pragma once
#include "VidPadMedia.h"
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#define VIDPAD_API __declspec(dllimport)
#endif

class VIDPAD_API VidPadTextures
{
public:
	VidPadTextures();
	~VidPadTextures();
	void InitTextures();
	void AssocTexture(VidPadMedia *Media);
private :

};

