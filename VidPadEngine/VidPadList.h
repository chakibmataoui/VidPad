#pragma once
#include "VidPadMedia.h"
#include "VidPadDecoder.h"
#include <vector>
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#define VIDPAD_API __declspec(dllimport)
#endif

using namespace std;
#define MAX_BUFFER 68

class VIDPAD_API VidPadList
{
public:
	//methods
	VidPadList();
	~VidPadList();
	//methods for list of key Very fast execution needed
	void AddKeyToList(char Key);
	void RemoveKeyFromList(char Key);
	//methods for file adding and deleting 
	void AddFileToList(char *File, char Key);
	void RemoveFileFromList(char Key);
	//methods for keyboard changing
	void AddPadToPlayList(char *File);
	void DeletePadFromList(char *File);
	//SetMaj
	void SetMaj(bool state);
	bool GetMaj();
	//SetBackgroundPath
	void SetBackgroundPath(char* Path);
	int AsciiToInt(char Key);//converts char to position
    //public proprieties 
	vector<char*> FileList; //List of file to decode
	vector<char*>PlayListPath; //List of projects to load 
	vector<VidPadMedia*> MediaList; //List of media to use
	VidPadMedia *BackgroundBuffer,*Foregroundbuffer;//Bakcground buffer loading
	vector<int> KeyList; //List of rendering keys 
	vector<int> KeyCodeList; //List of wParam keys list in azerty order
	char *BackgroundPath,*ForegroundPath;
private:
	bool CheckIfElementExists(int Key, vector<int> &tocheck);
	int KeyToInt(int Key, bool Maj);//converts in
	int GetElementPos(int Key, vector<int> &tocheck);
	bool Maj = false;
};

