#include "CTexture.h"
#include "main.h"

CTexture::CTexture()
{
	
}

CTexture::~CTexture()
{
    // ������ ����ϴ� ��Ʈ�� ������ �ٽ� ���� ��Ʈ�� ������ �����ϰ�
    SelectObject(mhDCMem, mhOldBitmap);
    // ���� ����ϴ� ��Ʈ�� ������ ���� �����Ѵ�
    DeleteObject(mhBitmap);

    // DC �� �����Ѵ�
    DeleteDC(mhDCMem);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC thDC, LPCWSTR tFileName)
{
    // ����ȭ�� dc �� ������� memory dc �� �����
    mhDCMem = CreateCompatibleDC(thDC);

    // ������ ��Ʈ�� ������ �����Ѵ�
    // ���⼭�� ���Ͽ��� �ε��Ͽ� ����� ���� �����ϰ� �ִ�
    //mhBitmap = (HBITMAP)LoadImage(hInst, TEXT("resources/bongbong_0.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    mhBitmap = (HBITMAP)LoadImage(hInst, tFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // ������ ������ ��Ʈ�� ������ ���� ��Ʈ�� ������ �����Ѵ�
    // ���ϰ����δ� ������ ����ϴ� ��Ʈ�� ������ ���ϵȴ�
    mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

    // ��Ʈ�� ������ �ڵ��� �̿��Ͽ� BITMAP info ������ ��´�
    mBitmapInfo;
    GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);

	return true;
}
