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
	static TrackingVideo * GetInstanceStartUp(string cascadePath, string fileNamePath);
	static TrackingVideo * GetInstance();
	static void Destroy();

private:
	string cascadeFrontalfilename;
	string fileName;
	struct Motor
	{
		vector<Point> centerPoint;
		int id;
	};
	int play;
	static TrackingVideo* instance;

	/*cv::Ptr<cv::CascadeClassifier> casCade;
	 mainDetector;
	cv::Ptr<DetectionBasedTracker::IDetector> trackingDetector;
*/
};

