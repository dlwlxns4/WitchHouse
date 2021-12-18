#include "TalkManager.h"
#include "../Util/RecourceId.h"

#define EXCEPTION "NoData"

void TalkManager::Init()
{
	//-------------------------------------------Obj------------------
	//----------------Log
	talkData.emplace(NORMAL_LOG_ID, vector<wstring>{L"썩은 통나무가 벌레의 집이 되어있다."});
	//----------------Grass
	talkData.emplace(ROUGH_GRASS_ID, vector<wstring>{L"삐죽삐죽한 억센 풀이 자라고있다."});
	//----------------Tree
	talkData.emplace(WITHER_TREE_ID, vector<wstring>{L"시들어버린 큰 나무가 있다."});
	talkData.emplace(GREEN_TREE_ID, vector<wstring>{L"파릇파릇하게 우거진 큰 나무가 있다."});




	//--------------------------------------------Item----------------
	itemTalkData.emplace(1, vector<wstring>{L"녹이 슬은 날붙이가 떨어져 있다.", L"가져간다.", L"가져가지 않는다."});
}

void TalkManager::SaveTalkData(int referenceId)
{
	vecTalkData = GetTalkData(referenceId);
}

vector<wstring> TalkManager::GetVecTalkData()
{
	return vecTalkData;
}

vector<wstring> TalkManager::GetTalkData(int referenceId)
{
	auto data = talkData.find(referenceId);
	if (data != talkData.end())
	{
		return (data->second);
	}
	vector<wstring> empty;
	return empty;
}
