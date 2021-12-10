#include "Image.h"
#include "Manager/ImageManager.h"


#pragma comment(lib, "msimg32.lib")





HRESULT Image::Init(const wchar_t* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(ImageManager::GetInstance()->GethWnd());

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(ImageManager::GetInstance()->GethInstance(), fileName, IMAGE_BITMAP, width, height,
		LR_LOADFROMFILE);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// ���� ������ DC 
											// �⺻������ Bitmap�� ����Ǿ� �ִ�.
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(ImageManager::GetInstance()->GethWnd(), hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}



void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDc);

		delete imageInfo;
		imageInfo = nullptr;
	}
}

void Image::Render(HDC hdc)
{
	BitBlt(hdc,				// ���� ������ DC
		0,					// ����� ��Ʈ���� ���� ��ġ x
		0,					// ����� ��Ʈ���� ���� ��ġ y
		imageInfo->width,	// ���� ������ ���� ũ��
		imageInfo->height,	// ���� ������ ���� ũ��
		imageInfo->hMemDc,	// ���� DC
		0,					// ���� ��Ʈ�� ���� ���� ��ġ x
		0,					// ���� ��Ʈ�� ���� ���� ��ġ y
		SRCCOPY);			// ���� �ɼ�
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDc,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,				// ���� ������ DC
			destX - (imageInfo->width / 2),				// ����� ��Ʈ���� ���� ��ġ x
			destY - (imageInfo->height / 2),			// ����� ��Ʈ���� ���� ��ġ y
			imageInfo->width,	// ���� ������ ���� ũ��
			imageInfo->height,	// ���� ������ ���� ũ��
			imageInfo->hMemDc,	// ���� DC
			0,					// ���� ��Ʈ�� ���� ���� ��ġ x
			0,					// ���� ��Ʈ�� ���� ���� ��ġ y
			SRCCOPY);			// ���� �ɼ�
	}
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY, float scale/* = 1.0f*/)
{
	// frameX : 0, frameY : 0 => ���� (68 * 0, 0) �󸶳� �����Ұǰ� (68, 104)
	// frameX : 1, frameY : 0 => ���� (68 * 1, 0)  (68, 104)
	// frameX : 2, frameY : 0 => ���� (68 * 2, 0)  (68, 104)
	// frameX : 3, frameY : 0 => ���� (68 * 3, 0)  (68, 104)

	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->frameWidth / 2),
			destY - (imageInfo->frameHeight / 2),
			(int)(imageInfo->frameWidth * scale),
			(int)(imageInfo->frameHeight * scale),	// ��ü ������ ��
			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			imageInfo->frameWidth, imageInfo->frameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,				// ���� ������ DC
			destX - (imageInfo->frameWidth / 2),		// ����� ��Ʈ���� ���� ��ġ x
			destY - (imageInfo->frameHeight / 2),		// ����� ��Ʈ���� ���� ��ġ y
			imageInfo->frameWidth,	// ���� ������ ���� ũ��
			imageInfo->frameHeight,	// ���� ������ ���� ũ��
			imageInfo->hMemDc,	// ���� DC
			imageInfo->frameWidth * frameX,				// ���� ��Ʈ�� ���� ���� ��ġ x
			imageInfo->frameHeight * frameY,			// ���� ��Ʈ�� ���� ���� ��ġ y
			SRCCOPY);			// ���� �ɼ�
	}
}

void Image::Render(HDC hdc, int destX, int destY, int imageSizeX, int imageSizeY, int startPosX, int startPosY, int sizeX, int sizeY)
{

	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			destX,				//�̹����� ����� ��ġ
			destY,
			imageSizeX,						//����� �̹����� �ʺ� ����
			imageSizeY,
			imageInfo->hMemDc,
			startPosX, //										//������ �̹����� ��������
			startPosY, //
			sizeX,							// ���� �̹����κ��� �ش�ũ�⸸ŭ �߶� �̹����� �ʺ� ����
			sizeY,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,				// ���� ������ DC
			destX - (imageInfo->frameWidth / 2),		// ����� ��Ʈ���� ���� ��ġ x
			destY - (imageInfo->frameHeight / 2),		// ����� ��Ʈ���� ���� ��ġ y
			imageInfo->frameWidth,	// ���� ������ ���� ũ��
			imageInfo->frameHeight,	// ���� ������ ���� ũ��
			imageInfo->hMemDc,	// ���� DC
			imageInfo->frameWidth,				// ���� ��Ʈ�� ���� ���� ��ġ x
			imageInfo->frameHeight,			// ���� ��Ʈ�� ���� ���� ��ġ y
			SRCCOPY);			// ���� �ɼ�
	}
}

void Image::Render(HDC hdc, int destX, int destY, int startPosX, int startPosY, int sizeX, int sizeY, BLENDFUNCTION ftn)
{

	AlphaBlend(
		hdc,
		destX,				//�̹����� ����� ��ġ
		destY,
		(int)(imageInfo->frameWidth),						//����� �̹����� �ʺ� ����
		(int)(imageInfo->frameHeight),
		imageInfo->hMemDc,
		startPosX, //										//������ �̹����� ��������
		startPosY, //
		sizeX,							// ���� �̹����κ��� �ش�ũ�⸸ŭ �߶� �̹����� �ʺ� ����
		sizeY,
		ftn
	);
}

void Image::Render(HDC hdc, int destX, int destY, int startPosX, int startPosY, int imageSizeX, int imageSizeY, int sizeX, int sizeY, BLENDFUNCTION ftn)
{

	AlphaBlend(
		hdc,
		destX,				//�̹����� ����� ��ġ
		destY,
		imageSizeX,						//����� �̹����� �ʺ� ����
		imageSizeY,
		imageInfo->hMemDc,
		startPosX, //										//������ �̹����� ��������
		startPosY, //
		sizeX,							// ���� �̹����κ��� �ش�ũ�⸸ŭ �߶� �̹����� �ʺ� ����
		sizeY,
		ftn
	);
}



