#include "TalkManager.h"
#include "../Util/RecourceId.h"

#define EXCEPTION "NoData"

void TalkManager::Init()
{
	//-------------------------------------------Obj------------------
	//----------------Log
	talkData.emplace(NORMAL_LOG_ID, vector<wstring>{L"���� �볪���� ������ ���� �Ǿ��ִ�."});
	//----------------Grass
	talkData.emplace(ROUGH_GRASS_ID, vector<wstring>{L"���׻����� �＾ Ǯ�� �ڶ���ִ�."});
	//----------------Tree
	talkData.emplace(WITHER_TREE_ID, vector<wstring>{L"�õ����� ū ������ �ִ�."});
	talkData.emplace(GREEN_TREE_ID, vector<wstring>{L"�ĸ��ĸ��ϰ� ����� ū ������ �ִ�."});




	//--------------------------------------------Item----------------
	itemTalkData.emplace(0, vector<wstring>{
		L"���� ���� �����̰� ������ �ִ�.\n\n", 
		L"\t��������.\n\n\t�������� �ʴ´�.",
		L"���������� �տ� �־���."});
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
		isItem = false;
		return (data->second);
	}
	vector<wstring> empty;
	return empty;
}

void TalkManager::SaveItemTalkData(int referenceId)
{
	vecTalkData = GetItemTalkData(referenceId);
}

vector<wstring> TalkManager::GetVecItemTalkData()
{
	return vecTalkData;
}

vector<wstring> TalkManager::GetItemTalkData(int referenceId)
{
	auto data = itemTalkData.find(referenceId);
	if (data != itemTalkData.end())
	{
		isItem = true;
		return (data->second);
	}
	vector<wstring> empty;
	return empty;
}

bool TalkManager::GetIsItem()
{
	return isItem;
}
