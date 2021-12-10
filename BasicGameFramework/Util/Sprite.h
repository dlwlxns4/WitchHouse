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
	void Render(int posX, int posY, int currFrameX, int currFrameY);
	void Render(int posX, int posY);
	void Update(); 
	void Release();

	int GetWidth();
	int GetHeight();
};