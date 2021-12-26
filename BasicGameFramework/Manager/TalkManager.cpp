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
	//----------------Rose
	talkData.emplace(SMALL_ROSE_ID, vector<wstring>{L"���� ������ ���� ���� �ִ�."});
	talkData.emplace(HUGE_ROSE_ID, vector<wstring>{L"���� �� ������ �Ŵ��� ��̰� ���� ���� �ִ�."});
	talkData.emplace(POT_ROSE_ID, vector<wstring>{L"��̲����� ��ĵǾ� �ִ�."});
	//----------------Candle
	talkData.emplace(CANDLE_ID, vector<wstring>{L"������ �Ҳ��� ���ϰ� �Ϸ��̰� �ִ�."});
	//----------------Clock
	talkData.emplace(WALL_CLOCK_ID, vector<wstring>{L"Ŀ�ٶ� �����ð谡�ִ�.\n\n�ð�� �Ҹ��� �Բ� �ð��� ����Ű�� �ִ�."});

	//---------------Cat
	talkData.emplace(ID0_CAT, vector<wstring>{L"���������\n\n\t\"������ ���Ⱦ�?\""});
	talkData.emplace(ID0_CAT_SAVE, vector<wstring>{L"���������\n\n\t\"�ΰ��� ���⿡ ������ ������!\""});

	//---------------Lamp
	talkData.emplace(LIGHT_OFF_LAMP_ID, vector<wstring>{L"�Һ��� �����ִ�."});

	//--------------Cabinet
	talkData.emplace(NORMAL_CABINET_ID, vector<wstring>{L"\"���� ������� ���ƿ��� ����\"\n\n��� �����ִ�."});

	//Message
	talkData.emplace(WELCOME_MESSAGE_ID, vector<wstring>{L"���� ����� ����."} );
	talkData.emplace(TEDDY_MESSAGE_ID, vector<wstring>{L"���� �ٱ��Ͽ�."});
	//�� ��ü�� ����Ʈ�� ���� 

	//--------------------------------------------Item----------------
	itemTalkData.emplace(0, vector<wstring>{
		L"���� ���� �����̰� ������ �ִ�.\n\n", 
		L"\t��������.\n\n\t�������� �ʴ´�.",
			L"���������� �տ� �־���."});

	itemTalkData.emplace(2, vector<wstring>{
		L"���� ���� ���̿� �������� ���� �ִ�.\n\n",
			L"\t�������� �ݴ´�.\n\n\t�ƹ��͵� ���� �ʴ´�.",
			L"�������� �տ� �־���."});

	itemTalkData.emplace(3, vector<wstring>{
		L"�۾��� ���� ������ �ִ�.\n\n",
			L"\t��������.\n\n\t�������� �ʴ´�.",
			L"��罽�� �ɷ��־ ������ ���� ����."});
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

void TalkManager::SetIsItem(bool isItem)
{
	this->isItem = isItem;
}

void TalkManager::SetVecTalkTad(vector<wstring> data)
{
	vecTalkData = data;
}

void TalkManager::SetCurrInteractId(int id)
{
	currInteractId = id;
}


int TalkManager::GetCurrInteractId()
{
	return currInteractId;
}
