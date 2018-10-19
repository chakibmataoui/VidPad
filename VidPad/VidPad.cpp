// VidPad.cpp : définit le point d'entrée pour l'application.
//
#include "stdafx.h"
#include "VidPad.h"


#define MAX_LOADSTRING 100

// Variables globales :
LPCWSTR szTitle = L"VidPad";					// Le texte de la barre de titre
LPCWSTR szWindowClass = L"VIDPAD";			// le nom de la classe de fenêtre principale
// Pré-déclarations des fonctions incluses dans ce module de code :
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	// TODO: placez ici le code.
	/*Creation of the menu and icon without using ressource.h*/
	MSG msg;

	// Initialise les chaînes globales
	MyRegisterClass(hInstance);

	// Effectue l'initialisation de l'application :
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VIDPAD));

	// Boucle de messages principale :
	while (GetMessage(&msg,NULL,0,0))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			break;
	}
	return (int)msg.wParam;

}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Stocke le handle d'instance dans la variable globale
   hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP,
      CW_USEDEFAULT, 0, 1366, 789, NULL, MainScreenMenu, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

