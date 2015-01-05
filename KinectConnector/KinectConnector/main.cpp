#include "define.h"
#include "glBodyRenderer.h"
#include "KinectConnector.h"

using namespace cv;

int main(){
	SkeletonInfo tBodystruct;
	KinectConnector kinect;
	glBodyRenderer renderer;

	//Image allocation
	Mat KinectRGB, KinectDepth;
	KinectRGB.create(KINECT_COLOR_HEIGHT, KINECT_COLOR_WIDTH, CV_8UC4);
	KinectDepth.create(KINECT_DEPTH_HEIGHT, KINECT_DEPTH_WIDTH, CV_8UC4);

	cv::namedWindow("RGB", CV_WINDOW_KEEPRATIO);
	cv::namedWindow("DEPTH", CV_WINDOW_KEEPRATIO);

	renderer.InitializeRenderer(KINECT_COUNT, "Body");
	kinect.KinectInitialize(KinectSource_Color | KinectSource_Depth| KinectSource_Body | KinectSource_Face);

	while(1){
		kinect.GetColorImage(&KinectRGB);
		kinect.GetDepthImage(&KinectDepth);
		kinect.GetSkeletonPos(&tBodystruct, &KinectRGB, 0);
		kinect.FaceDetection(&tBodystruct, &KinectRGB);

		imshow("RGB", KinectRGB);
		imshow("DEPTH", KinectDepth);

		if(waitKey(OPENCV_WAIT_DELAY) == 27)	break;
	}

	renderer.DeInitializeRenderer();

	//Image release
	KinectRGB.release();
	KinectDepth.release();

	cv::destroyAllWindows();

	return 0;
}