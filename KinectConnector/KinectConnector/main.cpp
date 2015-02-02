#include "define.h"
#include "glBodyRenderer.h"
#include "KinectConnector.h"
#include "CalibMatReader.h"

using namespace cv;

int main(){
	CalibMatReader matReader;
	SkeletonInfo tBodystruct;
	KinectConnector kinect;
	glBodyRenderer renderer;
	HRESULT hr;

	//Image allocation
	Mat KinectRGB, KinectDepth;
	KinectRGB.create(KINECT_COLOR_HEIGHT, KINECT_COLOR_WIDTH, CV_8UC4);
	KinectDepth.create(KINECT_DEPTH_HEIGHT, KINECT_DEPTH_WIDTH, CV_8UC4);

	cv::namedWindow("RGB", CV_WINDOW_KEEPRATIO);
	cv::namedWindow("DEPTH", CV_WINDOW_KEEPRATIO);

	renderer.InitializeRenderer(KINECT_COUNT, "Body");
	renderer.WaitUntilThreadInit();
	kinect.KinectInitialize(KinectSource_Color | KinectSource_Depth| KinectSource_Body | KinectSource_Face);

	while(1){
		kinect.GetDepthImage(&KinectDepth);
		hr = kinect.GetColorImage(&KinectRGB);
		if(SUCCEEDED(hr))
			hr = kinect.GetSkeletonPos(&tBodystruct, &KinectRGB, 0);
		else
			continue;

		if(SUCCEEDED(hr))
			kinect.FaceDetection(&tBodystruct, &KinectRGB);
		else
			continue;

		renderer.SetBodyInfo(&tBodystruct);

		imshow("RGB", KinectRGB);
		imshow("DEPTH", KinectDepth);

		if(waitKey(OPENCV_WAIT_DELAY) == 27)	break;
	}

	renderer.DeInitializeRenderer();
	renderer.WaitUntilThreadDead();

	//Image release
	KinectRGB.release();
	KinectDepth.release();

	cv::destroyAllWindows();

	return 0;
}