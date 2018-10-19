// VidPadEngineDebug.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <VidPad.h>
#pragma comment(lib,"VidPadEngine.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	VidPadDecoder *decoder= new VidPadDecoder();
	VidPadMedia *mediaDest = new VidPadMedia();
	VidPadRender *Render = new VidPadRender();
	char *file = "C:/Users/mataoui/Desktop/RobotRock/A.mp4";
	decoder->GetMediaType(file,mediaDest);
	decoder->DecodeFile(file,mediaDest);
	mediaDest->~VidPadMedia();
	Render->~VidPadRender();
	decoder->~VidPadDecoder();
	return 0;
}