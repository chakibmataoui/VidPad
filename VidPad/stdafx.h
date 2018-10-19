// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
// Fichiers d'en-tête Windows :
#include <windows.h>

// Fichiers d'en-tête C RunTime
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

