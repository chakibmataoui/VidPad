#pragma once
#include "stdafx.h"
#include "UIFunctions.h"
#include "SetupVDP.h"
#include "VDPRender.h"

static HDC hdc = 0;
static HGLRC hglrc = 0;
static HINSTANCE hInst;								// instance actuelle
static int i = 0;
static std::future<void> Loadingthread;

//Main Windows Processing
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//OPENGL Functions
bool setupPixelFormatDesctiptor(HDC hdc);
void ResizeScreen();
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
