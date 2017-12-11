#include "realSense.h"
#if CAMERA_TYPE==REALSENSE_CAMERA
#include <conio.h>
#include <opencv2/opencv.hpp>
#include<iostream>
#include<stdio.h>

#include "primeSense.h"
#include "realSense.h"

//#include <pxcsensemanager.h>
#include "poseEstimation.h"
#include "DATA.h"

using namespace std;
using namespace cv;
//Primesense specific file, so functions are not valid/compiled if the camera is not primesense

void cameraModule::FunInitCameraParam()
{
	//peep();
	printf("There are %d connected RealSense devices.\n", ctx.get_device_count());
	if (ctx.get_device_count() == 0)
		exit(EXIT_FAILURE);

	dev = ctx.get_device(0);

	printf("\nUsing device 0, an %s\n", dev->get_name());
	printf("    Serial number: %s\n", dev->get_serial());
	printf("    Firmware version: %s\n", dev->get_firmware_version());

	// Configure depth to run at VGA resolution at 30 frames per second
	dev->enable_stream(rs::stream::color, 640, 480, rs::format::rgb8, 30);
	dev->enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 30);



	return;
}

int cameraModule::FunInitOnlineMode(int input_mode, char* filename)
{

	depthFrame = new IrisDepthPixel[640 * 480];
	colorFrame = new IrisRGB888Pixel[640 * 480];
	//rs_get_device_extrinsics(dev, RS_STREAM_DEPTH, RS_STREAM_COLOR, &extrin, &err);
	//	dev->get_extrinsics(rs::stream::depth,rs::stream::color);
	dev->start();
	for (int i = 0; i <100; i++)
		dev->wait_for_frames();
	return 0;
}


int cameraModule::FunCreateDepthAndColorStreams()
{

	return 0;
}


void cameraModule::recordStreams(int isRecord, int numargs, std::string filename)
{

}


//wait till stream starts/ stream starts to respond
int cameraModule::waitForStreamFuntion(int* changedIndex)
{
	return 0;
}


void cameraModule::readFrames()
{
	dev->wait_for_frames();
//	FILE* f = fopen("realsense.txt", "w");
//FILE* f2 = fopen("realsense_scale.txt", "w");
	cv::Mat color(Size(640, 480), CV_8UC3, (void*)dev->get_frame_data(rs::stream::color), cv::Mat::AUTO_STEP);
	cv::Mat depth(Size(640, 480), CV_16UC1, (void*)dev->get_frame_data(rs::stream::depth_aligned_to_color), cv::Mat::AUTO_STEP);
	for (int i = 0; i < 480; i++)
	{
		for (int j = 0; j < 640; j++)
		{
			depthFrame[i * 640 + j] = (uint16_t)((depth.at<uint16_t>(i, j))*1000*dev->get_depth_scale());
		//	fprintf(f, "%d\n", (uint16_t)((depth.at<uint16_t>(i, j))));
			//fprintf(f2, "%d\n", depthFrame[i * 640 + j]);
			colorFrame[i * 640 + j].r = color.at<cv::Vec3b>(i, j)[0];
			colorFrame[i * 640 + j].g = color.at<cv::Vec3b>(i, j)[1];
			colorFrame[i * 640 + j].b = color.at<cv::Vec3b>(i, j)[2];
		}
		
	}
	//fclose(f);
	//fclose(f2);
//	exit(1);

	//while (1)
	{
		//imshow("depth", depth);
		//waitKey(10);
	}
}

const void* cameraModule::getColordata()
{
	return (colorFrame);
}


const void* cameraModule::getDepthdata()
{

	return (depthFrame);

}


void cameraModule::stopStreamRecord(int isRecord, int numargs)
{
	if (isRecord && numargs <= 1)
	{
		//	recorder.stop();
	}
	dev->stop();
}

cameraModule::cameraModule()
{



}
bool cameraModule::isColorFrameValid()
{
	return 1;

}

bool cameraModule::isDepthFrameValid()
{
	return 1;

}

cameraModule::~cameraModule()
{
	delete colorFrame;
	delete depthFrame;


}


/********************************/
/* Check that there is no error */
void errorCheck(int nRetVal) {
	if (0) {
		fprintf(stderr, "Failed: %s\n");
		exit(1);
	}
}
/*************************/

#endif