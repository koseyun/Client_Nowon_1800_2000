﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//#include "CDX_Engine.h"

// directX11 버전은 Window sdk에 이제 포함되므로 (따로 설치하지 않고) 헤더를 포함하고 관련 라이브러리를 링크해주면 간단히 설정을 끝낼 수 있다
// 라이브러리 링크는 코드상에서 하겠다
// dx11
#include <d3d11_1.h>
#include <directxcolors.h>
#include <d3dcompiler.h>

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")