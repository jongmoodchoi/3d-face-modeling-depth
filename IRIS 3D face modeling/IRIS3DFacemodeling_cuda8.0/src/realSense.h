#pragma once

#include "sensorDef.h"
//#include "OpenNI.h"
//using namespace openni;
//the contents are defined only for realsense camera
#if(CAMERA_TYPE==REALSENSE_CAMERA)  
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <librealsense/rs.hpp> 
//#include <librealsense2/rs.hpp> 

// if the structure for another camera is different then , it has to be copied to new structure of IrisRGB pixel format 
//below is the format of this structure IrisRGB888Pixel
//typedef struct
//{
/* Red value of this pixel. */
//	uint8_t r;
/* Green value of this pixel. */
//	uint8_t g;
/* Blue value of this pixel. */
//	uint8_t b;
//} IrisRGB888Pixel;
// if the format of the feed is same then just do typedef as below

typedef struct
{
	/* Red value of this pixel. */
	uint8_t r;
	/* Green value of this pixel. */
	uint8_t g;
	/* Blue value of this pixel. */
	uint8_t b;

} IrisRGB888Pixel;

//depth pixel should be of 2 bytes usually
typedef uint16_t IrisDepthPixel;

class cameraModule
{
public:
	cameraModule();
	~cameraModule();

	void FunInitCameraParam();
	int FunInitOnlineMode(int input_mode, char* filename);
	int FunCreateDepthAndColorStreams();
	void recordStreams(int isRecord, int numargs, std::string filename);
	const void* getDepthdata();
	const void* getColordata();
	int waitForStreamFuntion(int* changedIndex);
	void readFrames();
	void stopStreamRecord(int isRecord, int numargs);
	bool isColorFrameValid();
	bool isDepthFrameValid();

	bool align_depth_to_color = true;

	//PXCImage::ImageData depthData;
//	PXCImage::ImageData colorData;

private:

	
	IrisDepthPixel* depthFrame;
	IrisRGB888Pixel* colorFrame;

	rs::device* dev;
	rs::context ctx;
	//rs2::device* dev;
	//rs2::context ctx;
	//rs2::pipeline pipe;

};

void errorCheck(int nRetVal);

#endif


