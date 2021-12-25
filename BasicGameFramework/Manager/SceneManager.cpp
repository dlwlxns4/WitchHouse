#include "../stdafx.h"

#include "../Scene/TempScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/TilemapToolScene.h"
#include "../Scene/MainScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameOverScene.h"

#include "SceneManager.h"
#include "ImageManager.h"
#include <d2d1.h>

SceneManager::~SceneManager() noexcept
{
	_currentScene = nullptr;
	_nextScene = nullptr;

	for (auto& elem : _scenes)
	{
		delete elem.second;
	}
	_scenes.clear();
}

void SceneManager::Init()
{
	_scenes[L"Title"] = new TitleScene();
	_scenes[L"Temp"] = new TempScene();
	_scenes[L"TilemapTool"] = new TilemapToolScene();
	_scenes[L"Main"] = new MainScene();
	_scenes[L"GameOver"] = new GameOverScene();

	_currentScene = _scenes[L"Title"];
	_currentScene->Init();
}

void SceneManager::Update()
{
	_currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	ImageManager::GetInstance()->GetRenderTarget()->BeginDraw();
	ImageManager::GetInstance()->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::WhiteSmoke));
	_currentScene->Render(hdc);
	ImageManager::GetInstance()->GetRenderTarget()->EndDraw();
}

void SceneManager::Release()
{
	_currentScene->Release();
}

bool SceneManager::IsSetNextScene() const noexcept
{
	return _nextScene != nullptr;
}

void SceneManager::SetNextScene(const wstring& name)
{
	ASSERT_CRASH(_nextScene == nullptr);
	ASSERT_CRASH(_scenes.end() != _scenes.find(name));

	_nextScene = _scenes[name];
}

void SceneManager::ChangeScene()
{
	if (_nextScene)
	{
		_currentScene->Release();

		_currentScene = _nextScene;
		_currentScene->Init();

		_nextScene = nullptr;
	}
}

bool SceneManager::IsMainScene()
{
	if (_currentScene == _scenes[L"Main"])
		return true;
}

Scene* SceneManager::GetCurrentScene()
{
	return _currentScene;
}

bool SceneManager::IsThatScene(wstring scene)
{
	if (_currentScene == _scenes[scene])
	{
		return true;
	}
	return false;
}
