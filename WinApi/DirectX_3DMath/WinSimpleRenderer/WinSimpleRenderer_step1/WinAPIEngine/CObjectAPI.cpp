#include "CObjectAPI.h"
#include "CAPI_Engine.h"

CObjectAPI::CObjectAPI() :
	CRef(), mPosition() // mVelocity()
{

}
CObjectAPI::~CObjectAPI()
{

}

void CObjectAPI::SetEngine(CAPI_Engine* tpEngine)
{
	mpEngine = tpEngine;
}
