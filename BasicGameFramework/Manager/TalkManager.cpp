#include "TalkManager.h"
#include "../Util/RecourceId.h"

#define EXCEPTION "NoData"

void TalkManager::Init()
{
	talkData.emplace(NORMAL_LOG_ID, vector<wstring>{L"���� �볪���� ������ ���� �Ǿ��ִ�."});


	talkData.emplace(ROUGH_GRASS_ID, vector<wstring>{L"���׻����� �＾ Ǯ�� �ڶ���ִ�."});

	talkData.emplace(WITHER_TREE_ID, vector<wstring>{L"�õ����� ū ������ �ִ�."});
	talkData.emplace(GREEN_TREE_ID, vector<wstring>{L"�ĸ��ĸ��ϰ� ����� ū ������ �ִ�."});


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
