#include "CTexture.h"
#include "main.h"

CTexture::CTexture()
{
	
}

CTexture::~CTexture()
{
    // 이전에 사용하던 비트맵 도구를 다시 현재 비트맵 도구로 설정하고
    SelectObject(mhDCMem, mhOldBitmap);
    // 현재 사용하던 비트맵 도구는 이제 해제한다
    DeleteObject(mhBitmap);

    // DC 도 해제한다
    DeleteDC(mhDCMem);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC thDC, LPCWSTR tFileName)
{
    // 현재화면 dc 를 기반으로 memory dc 를 만든다
    mhDCMem = CreateCompatibleDC(thDC);

    // 설정할 비트맵 도구를 생성한다
    // 여기서는 파일에서 로드하여 만드는 것을 가정하고 있다
    //mhBitmap = (HBITMAP)LoadImage(hInst, TEXT("resources/bongbong_0.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    mhBitmap = (HBITMAP)LoadImage(hInst, tFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // 위에서 생성한 비트맵 도구를 현재 비트맵 도구로 설정한다
    // 리턴값으로는 이전에 사용하던 비트맵 도구가 리턴된다
    mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

    // 비트맵 도구의 핸들을 이용하여 BITMAP info 정보를 얻는다
    mBitmapInfo;
    GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);

	return true;
}
