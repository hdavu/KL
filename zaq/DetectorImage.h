#pragma once
#include "CascadeDetectorAdapter.h"


class DetectorImage

{
public:
	
	DetectorImage( Mat src);
	~DetectorImage();
	Mat GetResult();

private:
	CascadeClassifier motor_cascade;
	CascadeClassifier car_cascade;
	Mat result;
};

