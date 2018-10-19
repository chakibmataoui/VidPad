#include "stdafx.h"
#include "VidPadDecoder.h"


VidPadDecoder::VidPadDecoder()
{
	pngdecoder = new VidPadPNGDecoder();
	MpegDecoder = new VidPadVideoMPEGDecoder();
}


VidPadDecoder::~VidPadDecoder()
{
	pngdecoder->~VidPadPNGDecoder();
	MpegDecoder->~VidPadVideoMPEGDecoder();
}

bool VidPadDecoder::DecodeFile(char* filename, VidPadMedia* Mediaout)
{
	//GET ENCODING TYPE
	//if (Mediaout->BufferLoaded)
		//Mediaout->Empty();
	GetMediaType(filename, Mediaout);
	switch (Mediaout->mediaInfo.Codec)
	{
	case IMAGE_PNG: {
						if (pngdecoder->DecodePNG(Mediaout, filename))
						{
							//Mediaout->AssociateTexture();
							return true;
						}
						break;
	case VIDEO_MPEG: {
						 if (MpegDecoder->DecodeFile(filename, Mediaout))
						 {
							 //Mediaout->AssociateTexture();
							 return true;
						 }
						 break;
	}
	}
	default:return false;
	}
	return false;
}
void VidPadDecoder::DecodeNextFrame(VidPadMedia* Mediaout)
{
	switch (Mediaout->mediaInfo.Codec)
	{
	case VIDEO_MPEG: {
		   MpegDecoder->GetFrame(Mediaout);
				 break;
	}
	}
}
bool VidPadDecoder::GetMediaType(char* filename, VidPadMedia* Mediaout)
{
	if (pngdecoder->CheckIfPNG(filename,Mediaout))
	{
		Mediaout->mediaInfo.Codec = IMAGE_PNG;
		return true;
	}
	else if (MpegDecoder->CheckIfMPEG(filename, Mediaout))
	{
		Mediaout->mediaInfo.Codec = VIDEO_MPEG;
		return true;
	}
	return false;
}