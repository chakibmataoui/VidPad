#pragma once
#include "stdafx.h"
#include <thread>
#include <VidPad.h>

//KeyBoardFunctions 
void AddInputKey(int Key);
void DeleteInputKey(int Key);
void SetNewBackground(int Key);
void SetupKey(VidPadRender *Render,VidPadList *List,UINT message,WPARAM wParam);
void SetUpNextFrames(VidPadList *List, VidPadDecoder *Decoder,VidPadRender *Renderer);
//MultiThread
static std::vector<std::future<void>> NextFrames(26);