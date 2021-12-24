#pragma once

#include "Component.h"

#include <vector>
#include <array>

using namespace std;

class Astar : public Component
{
	struct Pos
	{
		int X;
		int Y;

		bool operator<(const Pos& other) const { return (X < other.X) && (Y < other.Y); }
		bool operator==(const Pos& other) const { return X == other.X && Y == other.Y; }
		bool operator!=(const Pos& other) const { return !(*this == other); }
	};

public:
	using Component::Component;
	virtual ~Astar() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnTrigger() override;

	void DoAstar();
	void PressPlayer();
	void SetPlayerPos();
	int Heuristic(Pos a, Pos b);


private:
	vector<vector<int>> f;
	vector<vector<int>> map;

	Pos start;
	Pos end;
	float delay = 0;

	bool isFind = false;
	bool isFinish = false;
	bool isJump = true;
};

