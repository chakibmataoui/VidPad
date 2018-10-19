#include "stdafx.h"
#include "SetupVDP.h"

void LoadFileList(VidPadList *List)
{
	//Here all the project reading functions 
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/A.mp4", 'a');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/z.png", 'z');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/e.png", 'e');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/r.png", 'r');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/t.png", 't');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/y.png", 'y');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/q.png", 'q');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/s.png", 's');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/d.png", 'd');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/f.png", 'f');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/g.png", 'g');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/h.png", 'h');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/a.png", 'a');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/w.png", 'w');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/x.png", 'x');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/c.png", 'c');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/v.png", 'v');
	List->AddFileToList("C:/Users/mataoui/Desktop/RobotRock/b.png", 'b');

	//List->BackgroundPath = "C:/Users/mataoui/Desktop/RobotRock/A.mp4";
}
void DecodeFileList(VidPadList *List, VidPadDecoder *Decoder,VidPadRender *Render)
{

	for (int i = 0; i < MAX_BUFFER; i++){
		if (List->FileList[i] != "")
		{
			List->MediaList[i]->AddKeyFrame(0);
			if (Decoder->DecodeFile(List->FileList[i], List->MediaList[i]))
			{
				continue;
			}
		}
	}

	if (List->BackgroundPath != "")
		Decoder->DecodeFile(List->BackgroundPath, List->BackgroundBuffer);
	if (List->ForegroundPath != "")
		Decoder->DecodeFile(List->ForegroundPath, List->Foregroundbuffer);
	Render->BackgroundImage = List->BackgroundBuffer;
	Render->ForeGroundImage = List->Foregroundbuffer;
}

void ReleaseMemory(VidPadList *List, VidPadDecoder *Decoder,VidPadRender *Render)
{
	List->~VidPadList();
	Decoder->~VidPadDecoder();
	Render->~VidPadRender();
}
