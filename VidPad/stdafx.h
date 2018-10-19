// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclure les en-t�tes Windows rarement utilis�s
// Fichiers d'en-t�te Windows�:
#include <windows.h>

// Fichiers d'en-t�te C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <future>

//En Tete VidPad
#include <gl\GL.h>
#include <gl\GLU.h>
#include <vector>
#include <VidPad.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"VidPadEngine.lib")

