#include "stdafx.h"
#include "MainWindowProc.h"

//PFD
//OPENGl PFD
static bool drawn = false;
static bool isPadLoaded = false;
bool setupPixelFormatDesctiptor(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd, *ppfd;
	int pixelformat;
	ppfd = &pfd;
	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppfd->nVersion = 1;
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;
	ppfd->dwLayerMask = PFD_MAIN_PLANE;
	ppfd->iPixelType = PFD_TYPE_RGBA;
	ppfd->cColorBits = 32;
	ppfd->cDepthBits = 24;
	ppfd->cAccumBits = 0;
	ppfd->cStencilBits = 8;
	pixelformat = ChoosePixelFormat(hdc, ppfd);
	if ((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0)
	{
		MessageBox(NULL, L"Failed", L"Failed", MB_ICONWARNING);
		return false;
	}
	if (SetPixelFormat(hdc, pixelformat, ppfd) == false)
	{
		MessageBox(NULL, L"Failed", L"Failed", MB_ICONWARNING);
		return false;
	}
	return true;
}
/////WND PROC///////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	wchar_t test[256] = L"";

	switch (message)
	{
	case WM_CREATE:
		//MultiThread loading
		//UI Setup
		CreateMenuBar(hWnd);     
		hdc = GetDC(hWnd);
		if (!setupPixelFormatDesctiptor(hdc))
		{
			PostQuitMessage(0);
		}
		hglrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hglrc);
		//VidPadSetUp
		//OpengL init functions
		glEnable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_DITHER);
		glDisable(GL_FOG);
		glDisable(GL_LIGHTING);
		glDisable(GL_LOGIC_OP);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_TEXTURE_1D);
		glDisable(GL_TEXTURE_2D);
		glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
		glPixelTransferi(GL_RED_SCALE, 1);
		glPixelTransferi(GL_RED_BIAS, 0);
		glPixelTransferi(GL_GREEN_SCALE, 1);
		glPixelTransferi(GL_GREEN_BIAS, 0);
		glPixelTransferi(GL_BLUE_SCALE, 1);
		glPixelTransferi(GL_BLUE_BIAS, 0);
		glPixelTransferi(GL_ALPHA_SCALE, 1);
		glPixelTransferi(GL_ALPHA_BIAS, 0);
		//glEnable(GL_DEPTH_TEST);
		//glPixelTransferi(GL_UNPACK_ALIGNMENT,1);
		//glDisable()
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPixelZoom(1.0, -1.0);
		glRasterPos2i(-1, 1);
		//First Timer On 
		SetTimer(hWnd, NULL, 1000 / 60, NULL);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Analyse les sélections de menu :
		switch (wmId)
		{
		case IDM_OPENPAD :
			if (isPadLoaded)
			{
				MemoryList = new VidPadList();
			}
			LoadFileList(MemoryList);
			Loadingthread = std::async(std::launch::async, DecodeFileList, MemoryList, MediaDecoder, ScreenRender);
			//Loadingthread.wait();
			//MessageBox(NULL,L"Loading Finished",L"Message",MB_OK);
			isPadLoaded = true;
			break;
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_FULLSCREEN:  
			TurnFullscreen(hWnd, hdc);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		if (GetKeyState(VK_CAPITAL) == 1 || GetKeyState(VK_CAPITAL) == -128)
		{
			MemoryList->SetMaj(true);
		}
		switch (wParam)
		{
		case VK_CONTROL:
			ScreenRender->SetCtrl(true);
			break;
		case VK_TAB:
			ScreenRender->SetAlt(true);
			break;
		case VK_F11:
			TurnFullscreen(hWnd,hdc);
			break;
		case VK_SHIFT  :
			MemoryList->SetMaj(true);
			break;
		case VK_SPACE:
			if (MemoryList->GetMaj())
				ScreenRender->RenderFore = true;
			else
				ScreenRender->RenderBack = true;
			if (ScreenRender->GetCtrl())
			{
				if (!MemoryList->GetMaj())
					ScreenRender->BackgroundImage = MemoryList->BackgroundBuffer;
				else
					ScreenRender->ForeGroundImage = MemoryList->Foregroundbuffer;
			}
			break;
		default :
			SetupKey(ScreenRender, MemoryList, message, wParam);
			break;
		}
		break;
	case WM_KEYUP:
		if (GetKeyState(VK_CAPITAL) == 0 || GetKeyState(VK_CAPITAL) == 127)
		{
			MemoryList->SetMaj(false);
		}
		switch (wParam)
		{
		case VK_CONTROL:
			ScreenRender->SetCtrl(false);
			break;
		case VK_TAB:
			ScreenRender->SetAlt(false);
			break;
		case VK_SHIFT :
			MemoryList->SetMaj(false);
			break;
		case VK_SPACE:
			if (MemoryList->GetMaj())
				ScreenRender->RenderFore = false;
			else
				ScreenRender->RenderBack = false;
			break;
		default:
			SetupKey(ScreenRender,MemoryList, message, wParam);
			break;
		}
		break;
	case WM_TIMER :
		drawn = false;
		//Update frames
		SendMessage(hWnd, WM_PAINT, wParam, lParam);
		//Loop Fps
		if (drawn)
		{
			SetUpNextFrames(MemoryList, MediaDecoder, ScreenRender);
			SetTimer(hWnd, NULL, 1000 / 60, NULL);
		}
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		//VidPadRender
		ScreenRender->RenderNextFrame(MemoryList);
		//END
		EndPaint(hWnd, &ps);
		SwapBuffers(hdc);
		drawn = true;
		break;
	case WM_DESTROY:
		if (hglrc)
			wglDeleteContext(hglrc);
		if (hdc)
			ReleaseDC(hWnd, hdc);
		ReleaseMemory(MemoryList, MediaDecoder,ScreenRender);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Gestionnaire de messages pour la boîte de dialogue À propos de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
