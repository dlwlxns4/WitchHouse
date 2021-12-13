#include "TalkManager.h"

#define EXCEPTION "NoData"

void TalkManager::Init()
{
	talkData.emplace(10, vector<string>{"•üasdf"});

}

string TalkManager::GetTalkData(int referenceId)
{
	auto data = talkData.find(referenceId);
	if (data != talkData.end())
	{
		return (data->second)[0];
	}
	return EXCEPTION;
}
