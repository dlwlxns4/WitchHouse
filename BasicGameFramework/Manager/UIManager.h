#pragma once

#include "../Util/Singleton.h"

#include <unordered_map>
#include <vector>

using namespace std;


class UIManager : public Singleton<UIManager>
{
public:
	void SetTalkData(vector<string> data);
private:
};