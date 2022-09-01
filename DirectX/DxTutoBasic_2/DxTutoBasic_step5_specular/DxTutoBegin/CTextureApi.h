#pragma once
#include "framework.h"

/*
	�ؽ�ó �̹��� �����͸� �ٷ�� Ŭ����
*/
class CTextureApi
{
public:
	CTextureApi()
	{
		mpTextureRV = nullptr;
	}
	~CTextureApi()
	{

	}

	CTextureApi(const CTextureApi& t) = delete;

	bool Create(ID3D11Device* tpDevice, LPCWSTR tpFileName);
	void Destroy();

	// getter
	ID3D11ShaderResourceView* GetTexture() const
	{
		return mpTextureRV;
	}

private:
	// �ؽ��Ĵ� ���� �������� �߻�ȭ
	ID3D11ShaderResourceView* mpTextureRV = nullptr;
};

