#include "CTexture.h"

CTexture::CTexture(): mhDCMem(NULL)
{

}
CTexture::~CTexture()
{
	//������ ����ϴ� ��Ʈ�� ������ �ٽ� ���� ��Ʈ�� ������ �����ϰ� 
	SelectObject(mhDCMem, mhOldBitmap);
	//���� ����ϴ� ��Ʈ�� ������ ���� �����Ѵ�
	DeleteObject(mhBitmap);

	//DC�� �����Ѵ�
	DeleteDC(mhDCMem);

	//ȭ�� DC�� Release������ ( ����� �ȵ� )
	//�̰��� �޸� DC�̹Ƿ� �����Ѵ�
}


bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const wchar_t* tpFileName)
{
	//������ ������ ���� ��Ʈ���� �ε�����
	//window api�� �����ϴ� ����� �̿��Ѵ�

	//memory dc �� �����
	mhDCMem = CreateCompatibleDC(hDC);

	//������ ��Ʈ�ʵ����� �����Ѵ�. 
	//���⼭�� ���Ͽ��� �ε��Ͽ� ����� ���� �����ϰ� �ִ�
	mhBitmap = (HBITMAP)LoadImage(hInst, tpFileName, 
		IMAGE_BITMAP, 
		0, 0, 
		LR_LOADFROMFILE);

	//������ ������ ��Ʈ�� ������ ���� ��Ʈ�� ������ �����Ѵ�
	//���ϰ����δ� ������ ����ϴ� ��Ʈ�� ������ ���ϵȴ� 
	mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

	//��Ʈ�� ������ �ڵ��� �̿��Ͽ� 
	//BITMAP info ������ ��´� 
	GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);

	return TRUE;
}



bool CTexture::CreateBackBuffer(HINSTANCE hInst, HDC hDC)
{
	//memory dc �� �����
	mhDCMem = CreateCompatibleDC(hDC);

	//DDB

	//���� �����͸� �����Ͽ� ���� 
	//���� �Լ��� ����ϸ� DC�� ȣȯ�Ǵ� DDB�� �ٷ� ������ش�. (���Ǽ��� ����)
	mhBitmap = (HBITMAP)CreateCompatibleBitmap(hDC, 800, 600);//hDC�� nullptr�� �־ ����



	//������ ������ ��Ʈ�� ������ ���� ��Ʈ�� ������ �����Ѵ�
	//���ϰ����δ� ������ ����ϴ� ��Ʈ�� ������ ���ϵȴ� 
	mhOldBitmap = (HBITMAP)SelectObject(mhDCMem, mhBitmap);

	//��Ʈ�� ������ �ڵ��� �̿��Ͽ� 
	//BITMAP info ������ ��´� 
	GetObject(mhBitmap, sizeof(mBitmapInfo), &mBitmapInfo);


	return TRUE;
}
