#pragma once


class ID2D1Bitmap;
class Sprite
{
private:
	ID2D1Bitmap* pBitmap = nullptr;

	int maxFrameX = 0;
	int maxFrameY = 0;

public:
	void Init(const wchar_t* fileName);
	void PlayerRender(int posX, int posY, int currFrameX, int currFrameY, float opacity);
	void SlateRender(int posX, int posY, int slatePos);
	void Render(int posX, int posY, int currFrameX, int currFrameY, int maxFrameX, int maxFrameY, bool isSample);
	void Render(int posX, int posY, int currFrameX, int currFrameY);
	void Render(int posX, int posY, int currFrameX, int currFrameY, int sizeX, int sizeY);
	void Render(float startPosX, float startPosY, int posX, int posY, bool isTile);
	void Render(int startPosX, int startPosY, float opacity, int currFrameX, int currFrameY, int maxFrameX, int maxFameY);
	void Render(int posX, int posY, float opacity);
	void SizeRender(int posX, int posY, int sizeX, int sizeY, float opacity);
	void LoopRender(int posX, int posY, int renderPosX, int renderPosY);
	void Release();

	int GetWidth();
	int GetHeight();
};