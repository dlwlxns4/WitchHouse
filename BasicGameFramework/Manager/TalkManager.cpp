#include "TalkManager.h"

void TalkManager::Init()
{
	talkData.emplace(0, vector<string>{"��"});

}

string TalkManager::GetTalkData(int referenceId)
{
	auto data = (talkData.find(referenceId));

	return (data->second)[0];
}
