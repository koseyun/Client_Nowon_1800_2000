#include "CommandCenter.h"
#include <iostream>

#pragma region 싱글톤
CommandCenter* CommandCenter::_instance = NULL;

CommandCenter* CommandCenter::GetInstace()
{
    if (_instance == nullptr)
        _instance = new CommandCenter();
    return _instance;
}
#pragma endregion

/// <summary>
/// 모든 등록된 SCV 상태 갱신
/// SCV 놀고 있으면 일시킴
/// </summary>

void CommandCenter::UpdateAllSCVs()
{
    vector<SCV>::iterator iter = SCVs.begin();
    for (; iter != SCVs.end(); iter++)
    {
        // SCV 놀고 있으면 채굴하라고 함
        if (iter->state == SCV::STATE::IDLE)
            iter->DoMine();

        iter->UpdataState();
    }
}

/// <summary>
/// SCV 소환 가능하면 소환
/// </summary>
/// <returns> 소환성공 : true , 실패 : false </returns>
bool CommandCenter::TrySpwanSCV()
{
    if (_minerals > SCV_COST) {
        _minerals -= SCV_COST; // 미네랄 차감
        SpawnSCV();
        return true;
    }
    return false;
}

/// <summary>
/// SCV 소환
/// </summary>
void CommandCenter::SpawnSCV()
{
    new SCV();
    _unitSpawnCount++;
}

/// <summary>
/// SCV 에게 명령 내릴때 호출할 콜백
/// </summary>
/// <param name="id"> 유닛 번호 </param>
void CommandCenter::SCVCallBack(int id)
{
    std::cout << "SCV (Unit ID : " << id << ") 응답" << std::endl;
}

/// <summary>
/// SCV 콜백함수 등록 & 벡터에 등록
/// </summary>
void CommandCenter::Register(SCV& scv)
{
    scv.RegisterCallBack(SCVCallBack);
    SCVs.push_back(scv);
}

/// <summary>
/// 소환한 총 유닛 수
/// </summary>
int CommandCenter::GetUnitSpawnCount()
{
    return _unitSpawnCount;
}

/// <summary>
/// 미네랄 양 증가 및 현재 미네랄 수 출력
/// </summary>
void CommandCenter::IncreaseMinerals(int amount)
{
    _minerals += amount;
    std::cout << "현재 미네랄 :" << _minerals << std::endl;
}
