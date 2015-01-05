#pragma once
#include "Kinect.h"
#include "Kinect.Face.h"
#include <opencv.hpp>
#include <vector>

#define KINECT_COUNT			1
#define KINECT_DEPTH_WIDTH		512
#define KINECT_DEPTH_HEIGHT		424
#define KINECT_COLOR_HEIGHT		1080
#define KINECT_COLOR_WIDTH		1920

#define OPENCV_WAIT_DELAY		20
#define PI						3.141592653589


#define SWAP(a,b,t) ((t)=(a), (a)=(b), (b)=(t))

//Face information structure
typedef struct _faceinfo{
	bool bDetect;						//Face Detection ����� �ȵ̴���
	CameraSpacePoint Facepos;			//3d �������� Face ��ǥ
	//�� ȸ�� ����
	int yaw;
	int pitch;
	int roll;
}faceinfo;

//Single Body Structure;
typedef struct BodyInfo{
	Joint JointPos[JointType_Count];
	//cv::Point2d jointPoints[JointType_Count];
	UINT64 BodyID;
	faceinfo Face;
	float upperbodylen;
	float lowerbodylen;
	float spinedepth;
}BodyInfo;

typedef struct synconizedSkeletons{
	int Hid;
	int numObservingKinect;
	bool bObsevingKinect[KINECT_COUNT];
	BodyInfo InfoBody[KINECT_COUNT];

}synconizedSkeletons;


typedef struct synconizedSkeletonsAll{

	SYSTEMTIME	st;
	int numObservedBody;
	bool bObsevedBody[BODY_COUNT];
	synconizedSkeletons syncSkels[BODY_COUNT];

}synconizedSkeletonsAll;

//Store sensor out Body information
typedef struct SkeletonInfo{
	int Kinect_ID;
	int Count;												//���� �����ϰ� �ִ� ���̷��� ����
	SYSTEMTIME	st;
	BodyInfo InfoBody[BODY_COUNT];
}SkeletonInfo;

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

typedef enum _KinectSource KinectSource;

enum _KinectSource
{
	KinectSource_Color	= 0x1,
	KinectSource_Depth	= 0x2,
	KinectSource_Body	= 0x4,
	KinectSource_Face	= 0xC
} ;