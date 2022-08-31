#include "CTextureApi.h"
#include "DDSTextureLoader.h"

bool CTextureApi::Create(ID3D11Device* tpDevice, LPCWSTR tpFileName)
{
	HRESULT tResult;

	tResult = CreateDDSTextureFromFile(tpDevice, tpFileName, nullptr, &mpTextureRV);

	if (FAILED(tResult))
	{
		return false;
	}

	return true;
}
void CTextureApi::Destroy()
{
	if (mpTextureRV)
	{
		mpTextureRV->Release();
		mpTextureRV = nullptr;
	}
}