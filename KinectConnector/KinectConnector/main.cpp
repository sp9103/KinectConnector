#include "define.h"
#include "glBodyRenderer.h"
#include "KinectConnector.h"

using namespace cv;

int main(){
	KinectConnector kinect;
	glBodyRenderer renderer;

	renderer.InitializeRenderer(KINECT_COUNT, "Body");

	while(1){

		if(waitKey(OPENCV_WAIT_DELAY) == 27)	break;
	}

	kinect.KinectDestroy();
	renderer.DeInitializeRenderer();

	return 0;
}