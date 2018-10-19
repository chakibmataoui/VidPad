#include "stdafx.h"
#include "UIFunctions.h"


/*AddWinodws Creation
Description : 2 Settings and 1 OPENGL Wnd
*/
/*MENU
///////////Menu Description
|File     | |Pad    | |Display   | |Record  | |Help  | 
|Open Pad | |Next   | |FullScreen| |Start   | |Online|
|Open Play| |Preview| |PadScreen | |Stop    | |About |
|Exit     | |       | |Settings  | |Settings| |      |
*/
void CreateMenuBar(HWND hwnd)
{
	MainScreenMenu = CreateMenu();
	for (int j = 0; j < 5;j++)
	{
		MenuItems[j] = CreatePopupMenu();
	}
	//CreatMenuBar
	AppendMenu(MainScreenMenu, MF_POPUP, (UINT_PTR)MenuItems[0], L"File");
	AppendMenu(MainScreenMenu, MF_POPUP, (UINT_PTR)MenuItems[1], L"Pad");
	AppendMenu(MainScreenMenu, MF_POPUP, (UINT_PTR)MenuItems[2], L"Display");
	AppendMenu(MainScreenMenu, MF_POPUP, (UINT_PTR)MenuItems[3], L"Recording");
	AppendMenu(MainScreenMenu, MF_POPUP, (UINT_PTR)MenuItems[4], L"Help");
	SetMenu(hwnd, MainScreenMenu);
	//CreateMenuPops
	//FileMenu
	AppendMenu(MenuItems[0],MF_STRING,IDM_OPENPAD,L"Open Pad");
	AppendMenu(MenuItems[0], MF_STRING, IDM_OPENPLAY, L"Open Playlist");
	AppendMenu(MenuItems[0], MF_STRING, IDM_EXIT, L"Exit");
	//Pad
	AppendMenu(MenuItems[1], MF_STRING | MF_DISABLED, IDM_NEXT, L"Next Pad");
	AppendMenu(MenuItems[1], MF_STRING | MF_DISABLED, IDM_PREVIOUS, L"Previous Pad");
	//Display
	AppendMenu(MenuItems[2], MF_STRING , IDM_FULLSCREEN, L"FullScreen");
	AppendMenu(MenuItems[2], MF_STRING , IDM_PADSCREEN, L"Pad Screen");
	AppendMenu(MenuItems[2], MF_STRING , IDM_SETTINGS, L"Settings");
	//Record
	AppendMenu(MenuItems[3], MF_STRING ,IDM_STARTRECORDING , L"Start Recording");
	AppendMenu(MenuItems[3], MF_STRING, IDM_STOPRECORDING, L"Stop Recording");
	AppendMenu(MenuItems[3], MF_STRING, IDM_RECSETTINGS, L"Recording Settings");
	//Help
	AppendMenu(MenuItems[4], MF_STRING, IDM_ABOUT, L"About VidPad");
	AppendMenu(MenuItems[4], MF_STRING, IDM_ONLINEHELP, L"Online Help");

}
//TurnToFUll Screen Mode NOTE : ADD OPENGL RESIZE
void TurnFullscreen(HWND hwnd,HDC hdc)
{
	if (fullscreen == false)
	{
		HWND windows = GetDesktopWindow();
		GetClientRect(windows, &screenSize);
		SetMenu(hwnd, NULL);
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, screenSize.right, screenSize.bottom, SWP_SHOWWINDOW);
		glViewport(0, 0, screenSize.right, screenSize.bottom);
		float x = ((float)screenSize.right) / 1366, y = ((float)screenSize.bottom) / 789;
		glRasterPos2i(-1, 1);
		glPixelZoom(x,-y);
		glMatrixMode(GL_PROJECTION);
		ShowCursor(false);
		SwapBuffers(hdc);
		fullscreen = true;
	}
	else
	{
		SetMenu(hwnd, MainScreenMenu);
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 1366, 789, SWP_SHOWWINDOW);
		glViewport(0, 0, 1366, 768);
		glRasterPos2i(-1, 1);
		glPixelZoom(1.0, -1.0);
		ShowCursor(true);
		SwapBuffers(hdc);
		fullscreen = false;
	}
}
