#include "stdafx.h"
#include "VidPadList.h"


VidPadList::VidPadList()
{
	FileList.resize(MAX_BUFFER);
	MediaList.resize(MAX_BUFFER);
	for (int i = 0; i < MAX_BUFFER; i++) {
		FileList[i] = "";
		MediaList[i] = new VidPadMedia();
	}
	BackgroundPath = "";
	ForegroundPath = "";
	BackgroundBuffer = new VidPadMedia();
	Foregroundbuffer = new VidPadMedia();
}


VidPadList::~VidPadList()
{
	for (unsigned int i = 0; i < MediaList.size(); i++) {
		MediaList[i]->~VidPadMedia();
		delete MediaList[i];
	}
	BackgroundBuffer->~VidPadMedia();
	Foregroundbuffer->~VidPadMedia();
	FileList.clear();
	KeyList.clear();
	KeyCodeList.clear();
	MediaList.clear();
}
/*Methods for keylist*/
void VidPadList::AddKeyToList(char Key)
{
	if ((Key <= 90 && Key >= 65) || (Key >= 97 && Key <= 122))
	{
		if (!CheckIfElementExists(AsciiToInt(Key), KeyList))
		{
			KeyList.push_back(AsciiToInt(Key));
		}
	}
}
void VidPadList::RemoveKeyFromList(char Key)
{
	std::vector<int>::iterator pos;
	if ((Key <= 90 && Key >= 65) || (Key >= 97 && Key <= 122))
	{
		if (CheckIfElementExists(AsciiToInt(Key), KeyList))
		{
			if (GetElementPos(AsciiToInt(Key), KeyList) != -1)
			{
				KeyList.erase(KeyList.begin() + GetElementPos(AsciiToInt(Key), KeyList));
			}
		}
	}
}
/*Methods of file system
TODO : think of a way to share the same buffer for duplicate file
*/
void VidPadList::AddFileToList(char *File, char Key)
{
	int KeyD = AsciiToInt(Key);
	FileList[KeyD] = File;
}
void VidPadList::RemoveFileFromList(char Key)
{
	int KeyD = AsciiToInt(Key);
	FileList[KeyD] = "";
}
/*TOOLS*/
bool VidPadList::CheckIfElementExists(int Key, vector<int> &tocheck)
{
	for (unsigned int i = 0; i < tocheck.size(); i++)
	{
		if (tocheck[i] == Key)
		{
			return true;
		}
	}
	return false;
}
int VidPadList::GetElementPos(int Key, vector<int> &tocheck)
{
	for (unsigned  int i = 0; i < tocheck.size(); i++)
	{
		if (tocheck[i] == Key)
		{
			return i;
		}
	}
	return -1;
}
int VidPadList::AsciiToInt(char Key)
{
	if ((Key <= 90 && Key >= 65))
		return (int)Key - 39 ;
	else if ((Key >= 97 && Key <= 122))
		return (int)Key - 97;
}
int VidPadList::KeyToInt(int Key,bool Maj)
{
	return 0;
}
//MAJ FUn
void VidPadList::SetMaj(bool state)
{
	Maj = state;
}
bool VidPadList::GetMaj()
{
	return Maj;
}
//Path
void VidPadList::SetBackgroundPath(char* Path)
{
	BackgroundPath = Path;
}