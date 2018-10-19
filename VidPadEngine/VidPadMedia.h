#include <vector>
extern "C"
{
#include <libavformat\avformat.h>
#include <libavcodec\avcodec.h>
#include <libswscale\swscale.h>
}
#pragma once
#ifndef VIDPADEXPORT_DLL
#define VIDPAD_API __declspec(dllexport)
#else
#define VIDPAD_API __declspec(dllimport)
#endif

//DEFINE MEDIA TYPE FOR VIDPADDECODER
enum VIDPAD_API MediaCategory
{
	UNKNOWN_CATEGORY,
	IMAGE,
	VIDEO,
	COLOR,
	SHAPE
};
typedef struct{
	float r;
	float g;
	float b;
	float a;
} VIDPAD_API Color;
typedef enum {
	UNKNOWN,
	IMAGE_PNG,
	IMAGE_JPEG,
	IMAGE_GIF,
	VIDEO_GIF,
	VIDEO_H246,
	VIDEO_MPEG
}VIDPAD_API MediaType;

//MEDIA INFO FOR VIDPADRENDER
typedef struct
{
	MediaCategory categoryofmedia;
	MediaType Codec;
	unsigned int MediaHeight;
	unsigned int MediaWidth;
	unsigned int NumberOfFrames;
	unsigned int FrameRate;
	unsigned int sizeofMedia;

}VIDPAD_API MediaInfo;

class VIDPAD_API VidPadMedia
{
public:
	VidPadMedia();
	~VidPadMedia();
	//BUFFER MANIPULATION
	bool Empty();  	//EMPTY FOR REUSE
	void AllocateBuffer(size_t Size);
	//MEDIA INFO
	bool BufferLoaded = false; //To Test if there's a buffer or NULL
	Color MediaColor;
	MediaInfo mediaInfo;
	unsigned char *mediabuffer; //The Video Buffer if not void 
	unsigned int CurFrame; //Current Image rendered
	unsigned int StartFrame;
	unsigned int CurKeyFrame;
	//RENDERING
	void SetMediaColor(float r,float g,float b,float a);
	void RenderFrame(); //Render Any type of media in opengl
	void AddKeyFrame(int Frame);
	void NextFrame(); //Calculate Next Frame For Video Only
	void NextKeyFrame();
	//LIBAV VARS 
	std::vector<AVPacket> StreamPackets;
	AVPacket CurPacket;
	AVCodecContext *MediaDecoContext;
	AVFrame *OneFrame, *TransFrame;
	uint8_t *Tbuffer;
	struct SwsContext *SwCntx;
	int framestatus, videostream, sizeH, packetNum;
private :
	void RenderImage();
	void RenderColor();
	void RenderShape();
	void RenderVideo();
	std::vector<int> KeyFrames;
};