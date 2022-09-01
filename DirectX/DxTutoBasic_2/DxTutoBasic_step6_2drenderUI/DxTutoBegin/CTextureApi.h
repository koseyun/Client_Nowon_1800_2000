#pragma once
#include "framework.h"

/*
	텍스처 이미지 데이터를 다루는 클래스
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
	// 텍스쳐는 뷰라는 개념으로 추상화
	ID3D11ShaderResourceView* mpTextureRV = nullptr;
};

