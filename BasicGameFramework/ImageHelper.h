#pragma once
#include <opencv2/highgui.hpp>
#include "Image.h"

#pragma comment (lib, "opencv_world3416d")

using namespace cv;


class OpencvHelper
{
public:
	static Mat ReadImage(const char* path, int flag = 1)
	{
		Mat result = imread(path, flag);

		return result;
	}
};
