#include "stdafx.h"
#include "TrackingVideo.h"


TrackingVideo* TrackingVideo::instance = NULL;

TrackingVideo::TrackingVideo(string cascadePath, string fileNamePath)
{
	cascadeFrontalfilename = cascadePath;
	fileName = fileNamePath;
}

TrackingVideo::~TrackingVideo()
{
}


void TrackingVideo::Play()
{	
	cv::Ptr<cv::CascadeClassifier> cascade = makePtr<cv::CascadeClassifier>(cascadeFrontalfilename);
	cv::Ptr<DetectionBasedTracker::IDetector> MainDetector = makePtr<CascadeDetectorAdapter>(cascade);
	if (cascade->empty())
	{
		printf("Error: Cannot load %s\n", cascadeFrontalfilename.c_str());
	}

	cascade = makePtr<cv::CascadeClassifier>(cascadeFrontalfilename);
	cv::Ptr<DetectionBasedTracker::IDetector> TrackingDetector = makePtr<CascadeDetectorAdapter>(cascade);
	if (cascade->empty())
	{
		printf("Error: Cannot load %s\n", cascadeFrontalfilename.c_str());
		//return 2;
	}
	DetectionBasedTracker::Parameters params;
	params.minDetectionPeriod = 100;
	DetectionBasedTracker Detector(MainDetector, TrackingDetector, params);

	VideoCapture cap(fileName);
	if (!cap.isOpened())  // check if we succeeded
		printf("Error: Open video failed\n");


	Mat ReferenceFrame;
	Mat GrayFrame;
	vector<Rect> objectInThisFrame;
	vector<Rect> objectInThisFrame2;

	vector<Rect> objectInLastFrame;
	vector<int> yOfObject;

	
	bool saveThisFrame = false;
	int currentIndex = 1;
	int total = 0;
	vector<Motor> listMotor;
	play = 0;
	do
	{

		if (play % 2 == 0)
		{
			cap >> ReferenceFrame;
			Mat dst;
			if (ReferenceFrame.empty())
			{
				break;
			}

			//	--->x
			//	|
			//	|
			//	y

			//x.y.w.h

			// ID the area we will tracking
			Rect rec(0, ReferenceFrame.rows / 2 - 100, ReferenceFrame.cols, ReferenceFrame.rows / 2);
			Mat roi = ReferenceFrame(rec);

			//begin
			cvtColor(roi, GrayFrame, COLOR_BGR2GRAY);
			Detector.process(GrayFrame);
			Detector.getObjects(objectInThisFrame);

			//ID and put all the motor into a list
			for (size_t i = 0; i < objectInThisFrame.size(); i++)
			{
				int a = objectInThisFrame[i].x + objectInThisFrame[i].width / 2;
				int b = objectInThisFrame[i].y + objectInThisFrame[i].height / 2;
				rectangle(roi, objectInThisFrame[i], Scalar(0, 0, 255), 3, 8, 0);
				//circle(roi, Point(a, b), 4, Scalar(0, 0, 255), 3, 8, 0);

				Point centerOfThisMotor(a, b);
				if (listMotor.empty()) // the fisrt motor in list
				{
					Motor motor;
					motor.centerPoint.push_back(centerOfThisMotor);
					motor.id = currentIndex;
					currentIndex++;
					listMotor.push_back(motor);
					total++;
					saveThisFrame = true;
				}
				else
				{
					// the distance to determine this is a new motor or already in list is 25.sqrt(2)
					bool hasBefore = false;
					for (int xx = 0; xx < listMotor.size(); xx++) {
						vector<Point> line = listMotor[xx].centerPoint;
						if (!line.empty()) {
							Point beforeCenterPoint = line[line.size() - 1];
							int deltaX = abs(centerOfThisMotor.x - beforeCenterPoint.x);
							int deltaY = abs(centerOfThisMotor.y - beforeCenterPoint.y);
							if (deltaX < 15 && deltaY < 30)
							{
								hasBefore = true;
								listMotor[xx].centerPoint.push_back(centerOfThisMotor);
							}
						}
					}

					if (!hasBefore) // you are here, that mean the list is not empty and you are a new motor to the list
					{
						Motor motor;
						motor.centerPoint.push_back(centerOfThisMotor);
						motor.id = currentIndex;
						currentIndex++;
						listMotor.push_back(motor);
						total++;
						saveThisFrame = true;
					}
				}
			}


			roi.copyTo(ReferenceFrame(rec));

			rectangle(ReferenceFrame, rec, Scalar(0, 255, 0), 3, 8, 0);

			//string disp = "2 bánh : " + to_string(listMotor.size());
			string disp = "2 banh : " + to_string(total);

			putText(ReferenceFrame, disp, Point(5, 100), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 2);

			resize(ReferenceFrame, dst, cv::Size(ReferenceFrame.cols / 2, ReferenceFrame.rows / 2));

			if (saveThisFrame)
			{
				string name = "C:\\Users\\Administrator\\Desktop\\LUU\\xx" + to_string(total) + ".jpg";

				imwrite(name, ReferenceFrame);
				saveThisFrame = false;
			}

			imshow("Video", dst);
		}
		char key = waitKey(5);
		if (key == 'q')
			play++;
		if (key == 27)
			break;
	} while (true);

	Detector.stop();



}

void TrackingVideo::SetStatusOfPlay()
{
	play = (play++)%2;
}

int TrackingVideo::GetStatusOfPlay()
{
	return play;
}

TrackingVideo * TrackingVideo::GetInstanceStartUp(string cascadePath, string fileNamePath)
{
	if (instance == NULL)
	{
		instance = new TrackingVideo( cascadePath,  fileNamePath);
	}

	return instance;
}

TrackingVideo * TrackingVideo::GetInstance()
{
	return instance;
}

void TrackingVideo::Destroy()
{
	if (instance != NULL)
		delete instance;
	instance = NULL;
}





