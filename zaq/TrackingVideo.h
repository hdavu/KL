#pragma once
#include "CascadeDetectorAdapter.h"
class TrackingVideo : public CascadeDetectorAdapter
{
public:
	TrackingVideo(string casCade, string fileName);
	~TrackingVideo();

	
	void Play();
	void SetStatusOfPlay();
	int GetStatusOfPlay();

private:
	string cascadeFrontalfilename;
	string fileName;
	struct Motor
	{
		vector<Point> centerPoint;
		int id;
	};
	int play;

	/*cv::Ptr<cv::CascadeClassifier> casCade;
	 mainDetector;
	cv::Ptr<DetectionBasedTracker::IDetector> trackingDetector;
*/
};

