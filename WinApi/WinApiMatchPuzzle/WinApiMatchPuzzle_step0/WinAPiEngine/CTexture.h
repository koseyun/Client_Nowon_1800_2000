#pragma once

#include <windows.h>

/*
	��Ʈ�� �̹��� �����͸� �ٷ�� Ŭ����

*/
class CTexture
{
public:
	HDC mhDCMem;
	HBITMAP mhBitmap;
	HBITMAP mhOldBitmap;

	BITMAP mBitmapInfo;		//��Ʈ�� ����


public:
	CTexture();
	~CTexture();
	


	bool LoadTexture(HINSTANCE hInst, HDC hDC, const wchar_t* tpFileName);

	bool CreateBackBuffer(HINSTANCE hInst, HDC hDC);

};

