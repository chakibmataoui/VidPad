#include "VidPadPNGDecoder.h"
#include "lodepng.h"
#include <iostream>


VidPadPNGDecoder::VidPadPNGDecoder()
{
	filereader = NULL;
}


VidPadPNGDecoder::~VidPadPNGDecoder()
{
	filereader = NULL;
}   

bool VidPadPNGDecoder::CheckIfPNG(char *filename, VidPadMedia* Buffer)
{
	std::vector<unsigned char> PNGCheckBuf;
	std::vector<unsigned char, std::allocator<unsigned char>> PNGbuffer;
	unsigned int PNGwidth, PNGheight, PNGinitError;
	lodepng::load_file(PNGCheckBuf,filename);
	PNGinitError = lodepng::decode(PNGbuffer, PNGwidth, PNGheight, filename, LCT_RGBA, 8);
	if (PNGinitError == 0)
	{
		Buffer->mediaInfo.categoryofmedia = IMAGE;
		return true;
	}
	else
	{
		return false;
	}
}
bool VidPadPNGDecoder::DecodePNG(VidPadMedia *mediaDest ,char* filenameC)
{
	std::vector<unsigned char, std::allocator<unsigned char>> PNGbuffer;
	unsigned int PNGwidth, PNGheight = 0;
	unsigned int sizeH = 0;
	if(CheckIfPNG(filenameC,mediaDest))
	{
		//OPEN FILE FOR READ
		fopen_s(&filereader, filenameC, "rb");
		if (filereader != NULL)
		{
			//GET SIZE OF FILE
			fseek(filereader, 0, SEEK_END);
			size_t sizeofFile = ftell(filereader);
			if (sizeofFile > 0)
			{
				//LODEPNG FOR DECODING
				PNGinitError = lodepng::decode(PNGbuffer, PNGwidth, PNGheight,filenameC, LCT_RGBA, 8);
				if (PNGinitError == 0)
				{
					//GET MEDIA AND PNG INFORMATION 
					mediaDest->mediaInfo.FrameRate = 1;
					mediaDest->mediaInfo.NumberOfFrames = 1;
					mediaDest->mediaInfo.categoryofmedia = IMAGE;
					mediaDest->mediaInfo.MediaHeight = PNGheight;
					mediaDest->mediaInfo.MediaWidth = PNGwidth;
					mediaDest->mediaInfo.sizeofMedia = PNGbuffer.size();
					mediaDest->BufferLoaded = true;
					//Allocate Frames and Images
					//mediaDest->mediabuffer = new unsigned char*[1];
					mediaDest->AllocateBuffer(mediaDest->mediaInfo.sizeofMedia);
					//TRANSFORM VECTOR TO CHAR AND TURN PICTURE TO 180
					for (int h = 0 ; (unsigned int)h < mediaDest->mediaInfo.MediaHeight; h++)
					{
						for (int w = 0; (unsigned int)w < (mediaDest->mediaInfo.MediaWidth*4); w++)
						{
							mediaDest->mediabuffer[(h*mediaDest->mediaInfo.MediaWidth * 4) + w] = PNGbuffer[(h*mediaDest->mediaInfo.MediaWidth * 4) + w];
						}
					}
					fclose(filereader);
					return true;
				}
			}
		}
	}
	//IF PNG NOT VERIFIED RETURN FALSE
	return false;
}