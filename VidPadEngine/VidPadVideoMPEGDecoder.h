#pragma once
#include <iostream>
#include "VidPadMedia.h"
extern "C"
{
#include <libavformat\avformat.h>
#include <libswscale\swscale.h>
#include <libavutil\imgutils.h>
}
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#define VIDPAD_API __declspec(dllimport)
#endif

class VIDPAD_API VidPadVideoMPEGDecoder
{
public:
	VidPadVideoMPEGDecoder();
	~VidPadVideoMPEGDecoder();
	bool CheckIfMPEG(char *filename, VidPadMedia *Buffer);
	bool DecodeFile(char *FileName, VidPadMedia *Buffer);
	bool GetFrame(VidPadMedia *Buffer);
private :
};

