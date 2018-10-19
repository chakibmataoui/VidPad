#pragma once
#include "VidPadMedia.h"
#include "VidPadPNGDecoder.h"
#include "VidPadVideoMPEGDecoder.h"
#include <future>
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#defin VIDPAD_API __declspec(dllimport)
#endif

class VIDPAD_API VidPadDecoder
{
public:
	VidPadDecoder();
	~VidPadDecoder();
	bool DecodeFile(char* Filename,VidPadMedia* Mediaout);
	bool GetMediaType(char* filename, VidPadMedia* Mediaout);
	void DecodeNextFrame(VidPadMedia* MediaOut);
private :
	VidPadPNGDecoder *pngdecoder;
	VidPadVideoMPEGDecoder * MpegDecoder;
};

