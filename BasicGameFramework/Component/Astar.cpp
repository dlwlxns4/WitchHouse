#include "Astar.h"

#include "../stdafx.h"

#include <queue>
#include <math.h>
#include <unordered_map>

#include "../Manager/GameManager.h"
#include "../Manager/PhysicsManager.h"
#include "../Manager/ImageManager.h"
#include "../Manager/SceneManager.h"

#include "../Util/Timer.h"

#include "../Component/Player/PlayerSpriteRenderer.h"
#include "../Component/SizeAdjRenderer.h"

using namespace std;

#define INF 1e3
#define START_X 2
#define START_Y 4

void Astar::Init()
{
	start = { _owner->GetPosition().x / 32, _owner->GetPosition().y / 32 };

	f.clear();
	map.clear();

	for (int i = 0; i < 13; ++i)
	{
		f.emplace_back(17, INF);
		map.emplace_back(17, 0);
	}
	f[start.Y][start.X] = 0;

	unordered_set<pair<int, int>, pair_hash>* collision = PhysicsManager::GetInstance()->GetCollisionObj();
	for (auto pos : *collision)
	{
		map[pos.second][pos.first] = -1;
	}

	SetPlayerPos();
}

void Astar::Update()
{
	if (isFind == false)
	{
		DoAstar();
	}
	else
	{
		PressPlayer();
	}
}

void Astar::Render(HDC hdc)
{
	ImageManager::GetInstance()->DrawColliderRect(_owner->GetPosition().x / 32, _owner->GetPosition().y / 32);

}

void Astar::OnTrigger()
{
}

void Astar::DoAstar()
{

	for (int i = 0; i < 13; ++i)
		f.emplace_back(17, INF);
	f[start.Y][start.X] = 0;

	Pos path[13][17];
	path[start.Y][start.X] = start;

	priority_queue<pair<int, Pos>> pq;
	pq.emplace(0, start);

	int dy[] = { -1, 0,  1, 0 };
	int dx[] = { 0, 1,  0,  -1 };
	int dg[] = { 10, 10,  10,  10 };

	delay += Timer::GetDeltaTime();

	while (false == pq.empty())
	{
		int w = -pq.top().first;
		Pos pos = pq.top().second;
		pq.pop();

		if (f[pos.Y][pos.X] < w)
		{
			continue;
		}

		if (pos == end)
		{
			cout << "목표 찾음" << endl;
			break;
		}

		for (int i = 0; i < 4; ++i)
		{
			int ny = dy[i] + pos.Y;
			int nx = dx[i] + pos.X;

			if (ny < 0 || ny >= 13 || nx < 0 || nx >= 17)
			{
				continue;
			}

			if (map[ny][nx] == -1)
			{
				continue;
			}

			//f(x) : g(x) + h(x) = 가중치
			//g(x) : 해당 정점으로 이동하는데 비용
			//h(x) : 휴리스틱


			int nf = dg[i] + Heuristic({ nx, ny }, end);

			if (f[ny][nx] > nf)
			{
				f[ny][nx] = nf;

				path[ny][nx] = pos;

				pq.emplace(-f[ny][nx], Pos{ nx, ny });
			}
		}
	}

	Pos curr = end;
	while (curr != start)
	{
		if (start == path[curr.Y][curr.X])
		{
			break;
		}

		curr = path[curr.Y][curr.X];
	}

	if (delay >= 75)
	{
		int currFrameX = _owner->GetComponent<SizeAdjRenderer>()->GetFrameX();
		if (isJump == true)
		{
			currFrameX++;
			if (currFrameX > 2)
			{
				isJump = false;
				currFrameX--;
			}
		}
		else
		{
			currFrameX--;
			if (currFrameX < 0)
			{
				isJump = true;
				currFrameX++;
			}
		}
		_owner->GetComponent<SizeAdjRenderer>()->SetFrameX(currFrameX);

		POINT pos = _owner->GetPosition();
		

		int dir = 0;
		if (pos.x > curr.X*32)
		{
			dir = 0;
		}
		else if (pos.x < curr.X*32)
		{
			dir = 1;
		}
		else if (pos.y > curr.Y*32)
		{
			dir = 2;
		}
		else if (pos.y < curr.Y*32)
		{
			dir = 3;
		}

		int dx[4] = { -1, 1,0,0 };
		int dy[4] = { 0,0,-1,1 };
		delay = 0;
		_owner->SetPosition(pos.x + 16*dx[dir], pos.y + 16 * dy[dir]);
	}

	GameObject* player = GameManager::GetInstance()->GetPlayer();
	POINT playerPos = player->GetPosition();
	if (_owner->GetPosition().x == playerPos.x && _owner->GetPosition().y == playerPos.y)
	{
		isFind = true;
		player->GetComponent<PlayerMovement>()->SetActionStartegy(PlayerActionState::Null);
		_owner->GetComponent<SizeAdjRenderer>()->SetSprite(L"Image/Graphics/Obj/AstarTeddy_Find.png");
		_owner->GetComponent<SizeAdjRenderer>()->SetMaxFrame(6, 1);
		_owner->GetComponent<SizeAdjRenderer>()->SetFrameX(0);
	}
	Init();
}

void Astar::PressPlayer()
{
		delay += Timer::GetDeltaTime();
	if (isFinish == false)
	{
		if (delay > 100.0f)
		{
			GameManager::GetInstance()->GetPlayer()->GetComponent<PlayerSpriteRenderer>()->SetActive(false);
			delay = 0;
			int currFrameX = _owner->GetComponent<SizeAdjRenderer>()->GetFrameX();
			_owner->GetComponent<SizeAdjRenderer>()->SetFrameX(currFrameX+1);

			if (currFrameX + 1 >= 6)
			{
				isFinish = true;
			}
		}
	}
	else
	{
		if (delay >= 200.f)
		{
			SceneManager::GetInstance()->SetNextScene(L"GameOver");
		}
	}
}

void Astar::SetPlayerPos()
{
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	POINT pos = player->GetPosition();
	end = { pos.x / 32, pos.y / 32 };
	cout << end.X << " " << end.Y << endl;
	map[pos.y / 32][pos.x / 32] = 3;
}

int Astar::Heuristic(Pos a, Pos b)
{
	return abs(a.X - b.X) + abs(a.Y - b.Y);
}
