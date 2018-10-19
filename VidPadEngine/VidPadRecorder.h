#include <Windows.h>
#pragma once
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#define VIDPAD_API __declspec(dllimport)
#endif

enum VIDPAD_API codecs{
	MP4,AVI
};

class VIDPAD_API VidPadRecorder
{
public:
	VidPadRecorder();
	~VidPadRecorder();
	void StartRecording(char* destination, int frameRate, HWND screen);
	void StopRecording(char* destination);
};

