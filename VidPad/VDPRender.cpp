#include "stdafx.h"
#include "VDPRender.h"

void SetupKey(VidPadRender *Render,VidPadList *List,UINT message, WPARAM wParam)
{
	switch (message)
	{
	case WM_KEYDOWN :
		if (List->GetMaj())
		{
			if (Render->GetCtrl())
			{
				if ((char)wParam <= 90 && (char)wParam >= 65)
				{
					Render->BackgroundImage = List->MediaList[List->AsciiToInt((char)wParam)];
				}
			}
			else if(Render->GetAlt())
			{
				if ((char)wParam <= 90 && (char)wParam >= 65)
				{
					Render->ForeGroundImage = List->MediaList[List->AsciiToInt((char)wParam)];
				}
			}
			else
				List->AddKeyToList((char)wParam);
		}
		else
		{
			if (Render->GetCtrl())
			{
				if ((char)wParam <= 90 && (char)wParam >= 65)
				{
					Render->BackgroundImage = List->MediaList[List->AsciiToInt(tolower((char)wParam))];
				}
			}
			else if(Render->GetAlt())
			{
				if ((char)wParam <= 90 && (char)wParam >= 65)
				{
					Render->ForeGroundImage = List->MediaList[List->AsciiToInt(tolower((char)wParam))];
				}
			}
			else
				List->AddKeyToList(tolower((char)wParam));
		}
		break;
	case WM_KEYUP :
		List->RemoveKeyFromList((char)wParam);
		List->RemoveKeyFromList(tolower((char)wParam));
		if (List->GetMaj())
		{
			List->RemoveKeyFromList((char)wParam);
			List->MediaList[List->AsciiToInt((char)wParam)]->NextKeyFrame();

		}
		else
		{
			List->RemoveKeyFromList(tolower((char)wParam));
			List->MediaList[List->AsciiToInt(tolower((char)wParam))]->NextKeyFrame();
		}
		break;
	}
}
void SetUpNextFrames(VidPadList *List,VidPadDecoder *Decoder,VidPadRender *Renderer)
{
	for (unsigned int i = 0; i < List->KeyList.size(); i++)
	{
		if (List->MediaList[List->KeyList[i]]->BufferLoaded && List->MediaList[List->KeyList[i]]->mediaInfo.categoryofmedia == VIDEO)
		{
			Decoder->DecodeNextFrame(List->MediaList[List->KeyList[i]]);
		}
	}
	if (Renderer->BackgroundImage->mediaInfo.categoryofmedia == VIDEO && Renderer->BackgroundImage->BufferLoaded)
	{
		Decoder->DecodeNextFrame(Renderer->BackgroundImage);
	}
	if (Renderer->ForeGroundImage->mediaInfo.categoryofmedia == VIDEO && Renderer->ForeGroundImage->BufferLoaded)
	{
		Decoder->DecodeNextFrame(Renderer->ForeGroundImage);
	}
}