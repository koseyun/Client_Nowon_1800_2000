#pragma once
#include <Windows.h>

class CTexture
{
public:
	HDC mhDCMem;
	HBITMAP mhBitmap;
	HBITMAP mhOldBitmap;
	BITMAP mBitmapInfo;;
	
public:
	CTexture();
	~CTexture();

	bool LoadTexture(HINSTANCE hInst, HDC thDC, LPCWSTR tFileName);
	bool CreateBackBuffer(HINSTANCE hInst, HDC thDC);

};

