#pragma once
#include "stdafx.h"
#include <VidPad.h>
#include <vector>

//LoadinfVDP holds functions for loading files and keyboard system 
static VidPadList *MemoryList = new VidPadList();
static VidPadDecoder *MediaDecoder = new VidPadDecoder();
static VidPadRender *ScreenRender = new VidPadRender(); //Temporary just to test 
//initialize file and lists function
void LoadFileList(VidPadList *List);
void DecodeFileList(VidPadList *List, VidPadDecoder *Decoder,VidPadRender *Render);
//UNLOAD
void ReleaseMemory(VidPadList *List,VidPadDecoder *Decoder,VidPadRender *Render);

