
#include<iostream>
#include<stdio.h>

#include "primeSense.h"

#include "poseEstimation.h"
#include "DATA.h"

using namespace std;
//Primesense specific file, so functions are not valid/compiled if the camera is not primesense

#if(CAMERA_TYPE==PRIMESENSE_CAMERA)  
using namespace openni;
//camera module is specific for each camera, each camera file must implement basic functions/ 
//data structures of camera for providing depth and color streams

void cameraModule::FunInitCameraParam()
{
	rc = OpenNI::initialize();
	errorCheck(rc);
	printf("After initialization:\n%s\n", openni::OpenNI::getExtendedError());
}

int cameraModule::FunInitOnlineMode(int input_mode,char* filename)
{

	if (input_mode == MODE_ONLINE)
		rc = device.open(ANY_DEVICE);
	else
		rc = device.open(filename);

	if (rc != openni::STATUS_OK)
	{
		printf("SimpleViewer: Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 1;
	}
	errorCheck(rc);
	return 0;
}


int cameraModule::FunCreateDepthAndColorStreams()
{
	rc = sdepth.create(device, SENSOR_DEPTH);

	if (rc == STATUS_OK) {

		openni::VideoMode videoMode = sdepth.getVideoMode();
		videoMode.setResolution(640, 480);
		sdepth.setVideoMode(videoMode);

		if (openni::STATUS_OK != rc)
		{
			cout << "error: depth fromat not supprted..." << endl;
		}
		rc = sdepth.start();
		if (rc != STATUS_OK) {
			printf("Couldn't start depth stream:\n%s\n", oniGetExtendedError());
			sdepth.destroy();
		}
	}
	else {
		printf("Couldn't find depth stream:\n%s\n", oniGetExtendedError());
	}

	rc = scolor.create(device, SENSOR_COLOR);
	if (rc == STATUS_OK) {

		openni::VideoMode videoMode = scolor.getVideoMode();
		videoMode.setResolution(640, 480);
		scolor.setVideoMode(videoMode);

		if (openni::STATUS_OK != rc)
		{
			cout << "error: depth fromat not supprted..." << endl;
		}
		rc = scolor.start();
		if (rc != STATUS_OK) {
			printf("Couldn't start color stream:\n%s\n", oniGetExtendedError());
			scolor.destroy();
		}
	}
	else {
		printf("Couldn't find color stream:\n%s\n", oniGetExtendedError());
	}

	if (!sdepth.isValid() && !scolor.isValid()) {
		printf("No valid streams. Exiting\n");
		return 2;
	}

	if (device.isImageRegistrationModeSupported(IMAGE_REGISTRATION_DEPTH_TO_COLOR)) 
	{
		rc = device.setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
		errorCheck(rc);
	}
	m_streams[0] = &sdepth;
	m_streams[1] = &scolor;
	return 0;
}


void cameraModule::recordStreams(int isRecord, int numargs,std::string filename)
{

	if(isRecord && numargs <= 1)
	{
		recorder.create(filename.c_str());
		recorder.attach(sdepth, false);
		recorder.attach(scolor, false);
		recorder.start();
	}
}



int cameraModule::waitForStreamFuntion(int* changedIndex)
{

	rc = openni::OpenNI::waitForAnyStream(m_streams, 2, changedIndex);
	if (rc != openni::STATUS_OK)
	{
		printf("Wait failed\n");
		return 1;
	}
	errorCheck(rc);
	return 0;
}


void cameraModule::readFrames()
{
	rc = sdepth.readFrame(&depthFrame);
	errorCheck(rc);
	rc = scolor.readFrame(&colorFrame);
	errorCheck(rc);

}

const void* cameraModule::getColordata()
{
	if (colorFrame.isValid())
		return (colorFrame.getData());
	else return NULL;
}


const void* cameraModule::getDepthdata()
{
	return (depthFrame.getData());
	
}


void cameraModule::stopStreamRecord(int isRecord,int numargs)
{
	if (isRecord && numargs <= 1)
	{
		recorder.stop();
	}
}
cameraModule::cameraModule()
{
	openni::Status rc = openni::STATUS_OK;
	m_streams = new openni::VideoStream*[2];

}
bool cameraModule::isColorFrameValid()
{
	return (colorFrame.isValid());
}

bool cameraModule::isDepthFrameValid()
{
	return (depthFrame.isValid());
}

cameraModule::~cameraModule()
{
	OpenNI::shutdown();
	delete[] m_streams;
	
}

#endif



