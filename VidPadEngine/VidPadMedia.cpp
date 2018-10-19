#include "stdafx.h"
#include "VidPadMedia.h"


VidPadMedia::VidPadMedia()
{
	mediabuffer = NULL;
	mediaInfo.FrameRate = 0;
	mediaInfo.MediaHeight = 0;
	mediaInfo.MediaWidth = 0;
	mediaInfo.NumberOfFrames = 0;
	mediaInfo.categoryofmedia = UNKNOWN_CATEGORY;
	mediaInfo.Codec = UNKNOWN;
	mediaInfo.sizeofMedia = 0;
	CurFrame = 0;
	MediaColor = {0,0,0,0};
	BufferLoaded = false;
	//KeyFrame
	CurKeyFrame = 0;
	//in case of libav
	MediaDecoContext = NULL;
	OneFrame = NULL, TransFrame = NULL, Tbuffer = NULL, SwCntx = NULL, videostream = 0, packetNum = 0;
	av_init_packet(&CurPacket);

}


VidPadMedia::~VidPadMedia()
{
	//delete mediabuffer;
	mediaInfo.FrameRate = 0;
	mediaInfo.MediaHeight = 0;
	mediaInfo.MediaWidth = 0;
	mediaInfo.NumberOfFrames = 0;
	mediaInfo.categoryofmedia = UNKNOWN_CATEGORY;
	mediaInfo.Codec = UNKNOWN;
	mediaInfo.sizeofMedia = 0;
	CurFrame = 0;
	if (avcodec_is_open(MediaDecoContext) > 0)
		avcodec_close(MediaDecoContext);
	avcodec_free_context(&MediaDecoContext);
	av_frame_free(&OneFrame);
	av_frame_free(&TransFrame);
	av_free(Tbuffer);
	sws_freeContext(SwCntx);
	av_free_packet(&CurPacket);
	videostream = 0, packetNum = 0;
	for (int i = 0; i < StreamPackets.size(); i++)
		av_free_packet(&StreamPackets[i]);
}
void VidPadMedia::AllocateBuffer(size_t Size)
{
	mediabuffer = new unsigned char[Size];
	for (unsigned int i = 0; i < Size; i++)
		mediabuffer[i] = ' ';
}
bool VidPadMedia::Empty()
{
	BufferLoaded = false;
	delete[] mediabuffer;
	mediaInfo.FrameRate = 0;
	mediaInfo.MediaHeight = 0;
	mediaInfo.MediaWidth = 0;
	mediaInfo.NumberOfFrames = 0;
	mediaInfo.categoryofmedia = UNKNOWN_CATEGORY;
	mediaInfo.sizeofMedia = 0;
	CurFrame = 0;
	MediaColor = { 0, 0, 0, 0 };
	if (avcodec_is_open(MediaDecoContext) > 0)
		avcodec_close(MediaDecoContext);
	for (int i = 0; i < StreamPackets.size(); i++)
		av_free_packet(&StreamPackets[i]);
	return true;
}
void VidPadMedia::NextFrame()
{
	CurFrame++;
	if (CurFrame >= mediaInfo.NumberOfFrames)
	{
		CurFrame = 0;
	}
}
void VidPadMedia::NextKeyFrame()
{
	CurKeyFrame++;
	if (CurKeyFrame >= KeyFrames.size())
	{
		CurKeyFrame = 0;
	}
	if (KeyFrames.size() != 0)
		CurFrame = KeyFrames[CurKeyFrame];
}
void VidPadMedia::AddKeyFrame(int Frame)
{
	KeyFrames.push_back(Frame);
}
void VidPadMedia::RenderFrame()
{
	switch (mediaInfo.categoryofmedia)
	{
	case IMAGE:
		RenderImage();
		break;
	case VIDEO:
		RenderVideo();
		break;
	case COLOR:
		RenderColor();
		break;
	}
}
void VidPadMedia::SetMediaColor(float r,float g,float b,float a)
{
	MediaColor = { r, g, b, a };
	mediaInfo.categoryofmedia = COLOR;
}
void VidPadMedia::RenderImage()
{
	if (BufferLoaded)
	{
		glDrawPixels(mediaInfo.MediaWidth,mediaInfo.MediaHeight,GL_RGBA,GL_UNSIGNED_BYTE,mediabuffer);
	}
}
void VidPadMedia::RenderVideo()
{
	if (BufferLoaded)
	{
		glDrawPixels(mediaInfo.MediaWidth, mediaInfo.MediaHeight, GL_RGBA, GL_UNSIGNED_BYTE, mediabuffer);
	}
}
void VidPadMedia::RenderColor()
{
	glColor4f(MediaColor.r, MediaColor.g, MediaColor.b,MediaColor.a);
	glRectf(-1.0, -1.0, 1.0, 1.0);
}