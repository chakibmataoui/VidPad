#include "VidPadMedia.h"
#pragma once
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#define VIDPAD_API __declspec(dllimport)
#endif

#define PNG_ERROR_FILE 0
#define PNG_ERROR_ENCODER 1
#define PNG_ERROR_CORRUPT 2

class VIDPAD_API VidPadPNGDecoder
{
public:
	VidPadPNGDecoder();
	~VidPadPNGDecoder();
	bool CheckIfPNG(char *filename,VidPadMedia* Buffer); // FOR VIDPADDECODER
	bool DecodePNG(VidPadMedia *mediaDest,char *filenameC); //FOR VIDPADDECODER
	unsigned int PNGinitError;
private :
	FILE *filereader;
};

