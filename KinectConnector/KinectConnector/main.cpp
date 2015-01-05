#include "define.h"
#include "glBodyRenderer.h"
#include "KinectConnector.h"

using namespace cv;

int main(){
	KinectConnector kinect;
	glBodyRenderer renderer;

	renderer.InitializeRenderer(KINECT_COUNT, "Body");
	kinect.KinectInitialize(KinectSource_Color | KinectSource_Depth| KinectSource_Body | KinectSource_Face);

	while(1){

		if(waitKey(OPENCV_WAIT_DELAY) == 27)	break;
	}

	renderer.DeInitializeRenderer();

	return 0;
}