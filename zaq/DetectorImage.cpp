#include "stdafx.h"
#include "DetectorImage.h"

DetectorImage::DetectorImage(Mat src)
{

	motor_cascade.load("C:\\Users\\Administrator\\Desktop\\trainGUI\\Train\\2banh\\train2banh-13-10-6-(tam-thoi-lay-cai-nay)\\classifier\\cascade.xml");
	car_cascade.load("C:\\Users\\Administrator\\Desktop\\trainGUI\\Train\\4banh\\train4banh-13-10-4(lay-ban-nay)\\classifier\\cascade.xml");

	if (motor_cascade.empty())
	{
		printf("Error: Cannot load motor n");
	}

	if (car_cascade.empty())
	{
		printf("Error: Cannot load car n");
	}

#pragma region Declare



	//Detector only work on this arena
	// x,y,w,h


	//Rect rec(0, src.rows / 2 - 100, src.cols, src.rows / 2); 
	Rect rec(0, src.rows / 2 - 200, src.cols, src.rows / 2 + 200);

	Mat roi = src(rec);

	//draw that arena on screen
	rectangle(src, rec, Scalar(255), 8, 0);

	//founded vehicle is saved in 2 vector:
	vector<Rect> motors, cars;
#pragma endregion


	//the work begins
	motor_cascade.detectMultiScale(roi, motors, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 100), Size(100, 200));
	car_cascade.detectMultiScale(roi, cars, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(201, 201), Size(500, 500));



	// remove wrong motor 
	if (cars.size() > 0 && motors.size() > 0)
	{
		for (int i = cars.size() - 1; i >= 0; i--)
		{
			for (int j = motors.size() - 1; j >= 0; j--)
			{
				if (cars[i].contains(Point(motors[j].x + motors[j].width *0.5, motors[j].y + motors[j].height * 0.5)))
				{
					motors.erase(motors.begin() + j);
				}
			}
		}
	}

	//draw motors
	if (motors.size() > 0)
	{
		for (int i = 0; i < motors.size(); i++)
		{
			Point center(motors[i].x + motors[i].width*0.5, motors[i].y + motors[i].height*0.5);
			ellipse(roi, center, Size(motors[i].width*0.5, motors[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
			putText(roi, "Xe may " + to_string(i + 1), Point(motors[i].x, motors[i].y), 5, 1, Scalar(255, 0, 0));

		}
	}

	//draw cars
	if (cars.size() > 0)
	{
		for (int i = 0; i < cars.size(); i++)
		{
			Point center(cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5);
			ellipse(roi, center, Size(cars[i].width*0.5, cars[i].height*0.5), 0, 0, 360, Scalar(255, 0, 0), 4, 8, 0);
			//rectangle(roi,);
			putText(roi, "O to " + to_string(i + 1), Point(cars[i].x, cars[i].y), 5, 1, Scalar(255, 0, 0));

		}
	}


	//put back the result
	src.copyTo(result);
}

DetectorImage::~DetectorImage()
{
}

Mat DetectorImage::GetResult()
{
	return result;
}
