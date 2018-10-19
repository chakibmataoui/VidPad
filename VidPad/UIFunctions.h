#pragma once
#include "stdafx.h"
/*Menu's ID*/
//FILE
#define IDM_OPENPAD				105
#define IDM_OPENPLAY		    106
#define IDM_EXIT		  	    107
//PAD
#define IDM_NEXT				108
#define IDM_PREVIOUS			109
//DISPLAY
#define IDM_FULLSCREEN			110
#define IDM_PADSCREEN			111
#define IDM_SETTINGS			112
//RECORDING
#define IDM_STARTRECORDING		113
#define IDM_STOPRECORDING		114
#define IDM_RECSETTINGS			115
//HELP
#define IDM_ONLINEHELP			116
#define IDM_ABOUT				117
/*Buttons's ID*/

//Global vars
//MenuVars
static HMENU MainScreenMenu = NULL;
static HMENU MenuItems[5];
//Popup windows vars
static HWND AboutWindow = NULL;
static HWND SamplesWindow = NULL;
static HWND SettingsWindow = NULL;
static HWND VideoSettingsWindow = NULL;
//Static vars
static RECT screenSize; // for full screen
static bool fullscreen = false;
//UI init
void CreateAboutWindowScreen(HWND hwnd);
void CreateSampleWindowScreen(HWND hwnd);
void CreateSettingsWnd(HWND hwnd);
void CreateVideoSetWnd(HWND hwnd);
//MenuFunctions
void CreateMenuBar(HWND hwnd);
//File Menu
char* OpenPadWnd(HWND hwnd);
char* OpenPlaylistWnd(HWND hwnd);
//Pad
void LoadNextPad();
void LoadPrevPad();
//Display 
void TurnFullscreen(HWND hwnd,HDC hdc);
void DisplaySamplesWnd(HWND hwnd);
void OpenSettingsMenu(HWND hwnd);
//Record 
bool StartRecording(char* FileDestination);
bool StopRecording();
void OpenRecordSetting(HWND hwnd);
//Help
void OpenOnlineWeb(HWND hwnd);
void OpenAboutWnd(HWND hwnd);
