#ifndef PRIMESENSE_H
#define PRIMESENSE_H

#include "sensorDef.h"

//the contents are defined only for primesense camera
#if(CAMERA_TYPE==PRIMESENSE_CAMERA)  

#include "OpenNI.h"
using namespace openni;

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
typedef OniRGB888Pixel IrisRGB888Pixel ; 

//depth pixel should be of 2 bytes usually
typedef OniDepthPixel IrisDepthPixel ;

class cameraModule
{
public:
	cameraModule();
	~cameraModule();

	void FunInitCameraParam();
	int FunInitOnlineMode(int input_mode, char* filename);
	int FunCreateDepthAndColorStreams();
	void recordStreams(int isRecord, int numargs,std::string filename);
	const void* getDepthdata();
	const void* getColordata();
	int waitForStreamFuntion(int* changedIndex);
	void readFrames();
	void stopStreamRecord(int isRecord, int numargs);
	bool isColorFrameValid();
	bool isDepthFrameValid();

	const OniDepthPixel *pDepthMap;
	const OniRGB888Pixel* pImageMap;
private:
	openni::Status rc;
	openni::VideoStream sdepth, scolor;
	openni::VideoFrameRef depthFrame, colorFrame;
	openni::Device device;
	openni::VideoMode videoMode;
	openni::Recorder recorder;
	openni::VideoStream** m_streams;

};

#endif
#endif
