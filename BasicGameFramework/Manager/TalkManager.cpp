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
	//----------------Rose
	talkData.emplace(SMALL_ROSE_ID, vector<wstring>{L"작은 나무가 길을 막고 있다."});
	talkData.emplace(HUGE_ROSE_ID, vector<wstring>{L"겁이 날 정도로 거대한 장미가 길을 막고 있다."});
	talkData.emplace(POT_ROSE_ID, vector<wstring>{L"장미꽃으로 장식되어 있다."});
	//----------------Candle
	talkData.emplace(CANDLE_ID, vector<wstring>{L"양초의 불꽃이 묘하게 일렁이고 있다."});
	//----------------Clock
	talkData.emplace(WALL_CLOCK_ID, vector<wstring>{L"커다란 괘종시계가있다.\n\n시계는 소리와 함께 시간을 가르키고 있다."});

	//---------------Cat
	talkData.emplace(ID0_CAT, vector<wstring>{L"검은고양이\n\n\t\"정신은 차렸어?\""});
	talkData.emplace(ID0_CAT_SAVE, vector<wstring>{L"검은고양이\n\n\t\"인간이 여기에 있으면 위험해!\""});

	//---------------Lamp
	talkData.emplace(LIGHT_OFF_LAMP_ID, vector<wstring>{L"불빛이 꺼져있다."});

	//--------------Cabinet
	talkData.emplace(NORMAL_CABINET_ID, vector<wstring>{L"\"집이 원래대로 돌아오면 열어\"\n\n라고 써져있다."});

	//Message
	talkData.emplace(WELCOME_MESSAGE_ID, vector<wstring>{L"나의 방까지 오렴."} );
	talkData.emplace(TEDDY_MESSAGE_ID, vector<wstring>{L"곰을 바구니에."});
	//위 객체랑 퀘스트랑 엮자 

	//--------------------------------------------Item----------------
	itemTalkData.emplace(0, vector<wstring>{
		L"녹이 슬은 날붙이가 떨어져 있다.\n\n", 
		L"\t가져간다.\n\n\t가져가지 않는다.",
			L"정원가위를 손에 넣었다."});

	itemTalkData.emplace(2, vector<wstring>{
		L"선물 상자 더미에 곰인형이 기대어 있다.\n\n",
			L"\t곰인형을 줍는다.\n\n\t아무것도 하지 않는다.",
			L"곰인형을 손에 넣었다."});

	itemTalkData.emplace(3, vector<wstring>{
		L"작업대 위에 가위가 있다.\n\n",
			L"\t가져간다.\n\n\t가져가지 않는다.",
			L"쇠사슬에 걸려있어서 가져갈 수가 없다."});
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
