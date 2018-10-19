#include "stdafx.h"
#include "VidPadVideoMPEGDecoder.h"


VidPadVideoMPEGDecoder::VidPadVideoMPEGDecoder()
{
}


VidPadVideoMPEGDecoder::~VidPadVideoMPEGDecoder()
{
}
bool VidPadVideoMPEGDecoder::CheckIfMPEG(char *filename, VidPadMedia *Buffer)
{
	if (filename == "")
		return false;
	//Var init
	AVFormatContext *Context = NULL;
	//FUn init
	av_register_all();
	int error = avformat_open_input(&Context, filename, NULL, NULL);
	avformat_free_context(Context);
	if (error < 0)
		return false;
	else
		Buffer->mediaInfo.categoryofmedia = VIDEO;
	return true;
}
bool VidPadVideoMPEGDecoder::GetFrame(VidPadMedia* Buffer)
{
	//DECODING
	int ret = 0;
	Buffer->framestatus = 0;
	
	/*for (unsigned int i = Buffer->CurFrame; i < Buffer->StreamPackets.size(); i++)
	{
		Buffer->framestatus = 0;
		av_copy_packet(&Buffer->CurPacket, &Buffer->StreamPackets[i]);
		ret = avcodec_decode_video2(Buffer->MediaDecoContext, Buffer->TransFrame, &Buffer->framestatus, &Buffer->CurPacket);
		if (Buffer->framestatus != 0)
		{
			Buffer->CurPacket.data += ret;
			Buffer->CurPacket.size -= ret;
			//Buffer->CurFrame = i;
			break;
		}
	}*/
	av_copy_packet(&Buffer->CurPacket, &Buffer->StreamPackets[Buffer->CurFrame]);

	ret = avcodec_decode_video2(Buffer->MediaDecoContext, Buffer->TransFrame, &Buffer->framestatus, &Buffer->CurPacket);

	if (Buffer->CurFrame == Buffer->mediaInfo.NumberOfFrames)
	{
		Buffer->CurPacket.data  = NULL;
		Buffer->CurPacket.size = 0;

	}
	else
	{
		Buffer->CurPacket.data += ret;
		Buffer->CurPacket.size -= ret;
	}
	Buffer->NextFrame();
	if (Buffer->framestatus == 0)
	{
		return false;
	}
	sws_scale(Buffer->SwCntx, (uint8_t const* const*)Buffer->TransFrame->data, Buffer->TransFrame->linesize, 0, Buffer->MediaDecoContext->height, Buffer->OneFrame->data, Buffer->OneFrame->linesize);
	Buffer->mediabuffer = Buffer->OneFrame->data[0];
	return true;
}
bool VidPadVideoMPEGDecoder::DecodeFile(char *FileName, VidPadMedia* Buffer)
{
	//INIt vars
	AVFormatContext *DemuxContext = NULL;
	AVCodecContext *DecoFileinf = NULL;
	AVCodec *Codec = NULL;
	bool IsThereMedia = false;
	AVPacket TransPacket;
	//DEMUXING
	av_register_all();
	if (avformat_open_input(&DemuxContext, FileName,NULL, NULL) < 0)
		return false;
	if (avformat_find_stream_info(DemuxContext, NULL) < 0)
		return false;
	av_dump_format(DemuxContext, 0, FileName, 0);
	for (unsigned int i = 0; i < DemuxContext->nb_streams; i++)
	{
		if (DemuxContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			IsThereMedia = true;
			Buffer->videostream = i;
			DecoFileinf = DemuxContext->streams[i]->codec;
			break;
		}
	}
	if (IsThereMedia == false)
		return false;
	//DECODING
	Codec = avcodec_find_decoder(DecoFileinf->codec_id);
	if (Codec == NULL)
		return false;

	Buffer->MediaDecoContext = avcodec_alloc_context3(Codec);
	Buffer->MediaDecoContext->height = DecoFileinf->height;
	Buffer->MediaDecoContext->width = DecoFileinf->width;
	if (avcodec_copy_context(Buffer->MediaDecoContext, DecoFileinf) != 0)
		return false;
	if (avcodec_open2(Buffer->MediaDecoContext, Codec,NULL) < 0)
		return false;
	Buffer->OneFrame = av_frame_alloc();
	Buffer->TransFrame = av_frame_alloc();
	Buffer->Tbuffer = (uint8_t*)av_malloc(avpicture_get_size(PIX_FMT_RGBA, Buffer->MediaDecoContext->width, Buffer->MediaDecoContext->height)*sizeof(uint8_t));
	//DECONDING FRAMES
	while (av_read_frame(DemuxContext, &TransPacket) >= 0)
	{
		if (TransPacket.stream_index == Buffer->videostream && TransPacket.buf != NULL)
		{
			Buffer->StreamPackets.push_back(TransPacket);
		}
	}
	Buffer->SwCntx = sws_getContext(Buffer->MediaDecoContext->width, Buffer->MediaDecoContext->height, Buffer->MediaDecoContext->pix_fmt
		, Buffer->MediaDecoContext->width, Buffer->MediaDecoContext->height, PIX_FMT_RGBA, SWS_BICUBIC, NULL, NULL, NULL);
	/*int ret = 0;
	for (unsigned int i = 0; i < Buffer->StreamPackets.size(); i++)
	{
		Buffer->framestatus = 0;
		ret = avcodec_decode_video2(Buffer->MediaDecoContext, Buffer->TransFrame, &Buffer->framestatus, &Buffer->StreamPackets[i]);
		if (Buffer->framestatus != 0)
		{
			Buffer->StreamPackets[i].data += ret;
			Buffer->StreamPackets[i].size -= ret;
			Buffer->CurFrame = i;
			Buffer->StartFrame = i;
			break;
		}
	}
	if (!Buffer->framestatus)
		return false;*/
	avpicture_fill((AVPicture*)Buffer->OneFrame, Buffer->Tbuffer, PIX_FMT_RGBA, Buffer->MediaDecoContext->width, Buffer->MediaDecoContext->height);
	/*sws_scale(Buffer->SwCntx, ((AVPicture*)Buffer->TransFrame)->data, ((AVPicture*)Buffer->TransFrame)->linesize, 0, Buffer->MediaDecoContext->height, ((AVPicture*)Buffer->OneFrame)->data, ((AVPicture*)Buffer->OneFrame)->linesize);*/

	//TRANSLATING TO VIDPAD
	//VDPMEDIA INF

	Buffer->mediaInfo.FrameRate = Buffer->MediaDecoContext->framerate.num / Buffer->MediaDecoContext->framerate.den;
	Buffer->mediaInfo.MediaHeight = Buffer->MediaDecoContext->height;
	Buffer->mediaInfo.MediaWidth = Buffer->MediaDecoContext->width;
	Buffer->mediaInfo.NumberOfFrames = Buffer->StreamPackets.size() - 1;
	Buffer->mediaInfo.sizeofMedia = avpicture_get_size(PIX_FMT_RGBA, Buffer->MediaDecoContext->width, Buffer->MediaDecoContext->height);
	Buffer->AllocateBuffer(avpicture_get_size(PIX_FMT_RGBA, Buffer->MediaDecoContext->width, Buffer->MediaDecoContext->height));
	Buffer->BufferLoaded = true;
	Buffer->mediaInfo.categoryofmedia = VIDEO;
	//Buffer->mediabuffer = Buffer->OneFrame->data[0];
	//Buffer->CurPacket = Buffer->StreamPackets[0];
	GetFrame(Buffer);
	//FREEING
	avformat_free_context(DemuxContext);
	av_free_packet(&TransPacket);
	DemuxContext = NULL, DecoFileinf = NULL ;
	delete DemuxContext, DecoFileinf;
	return true;
}