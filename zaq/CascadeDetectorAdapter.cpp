#include "stdafx.h"
#include "CascadeDetectorAdapter.h"


CascadeDetectorAdapter::CascadeDetectorAdapter()
{
}

void CascadeDetectorAdapter::detect(const Mat & Image, std::vector<Rect>& objects)
{
	Detector->detectMultiScale(Image, objects, scaleFactor, minNeighbours, 0, minObjSize, maxObjSize);
}
