#include "define.h"

using namespace cv;

//���̷��� �׸��� �κ��� �Ķ����
static const float c_JointThickness = 3.0f;
static const float c_TrackedBoneThickness = 6.0f;
static const float c_InferredBoneThickness = 1.0f;
static const float c_HandSize = 30.f;

class KinectConnector
{
public:
	KinectConnector(void);
	~KinectConnector(void);

	//Kinect Initialize
	HRESULT KinectInitialize();

	//Get Color Opencv Image. (1920*1080)
	//Image must allocated.(size: 1920*1080, CV_8UC4)
	void GetColorImage(Mat *src);

	//Get Depth Opencv Image. (512*424)
	//Image must allocated. (size: 512*424, CV_8UC4)
	void GetDepthImage(Mat *src);

	//Get Body joint position. (joint count : 25)
	//and Draw Opencv Image.
	//if mode = 1, Draw DepthScale. so src = DepthImage
	//else if mode = 2, Draw ColorScale. so src = ColorImage.
	void GetSkeletonPos(SkeletonInfo *m_SkeletonInfo, Mat *src, int mode);

	//Kinect sensor close.
	void KinectDestroy();

	//Return Kinect Unique ID
	void GetKinectID(WCHAR *KinectID);

	void BasisCalibration(SkeletonInfo* m_SkeletonInfo);

	//Set intrinsic & extrinsic mat
	void SetKmat(Mat src);
	void SetRmat(Mat src);
	void SetTmat(Mat src);

private:
	IKinectSensor*			m_pKinectSensor;
	IColorFrameReader*		m_pColorFrameReader;
	IDepthFrameReader*		m_pDepthFrameReader;
	IBodyFrameReader*		m_pBodyFrameReader;
	ICoordinateMapper*		m_pCoordinateMapper;

	RGBQUAD*				m_pColorRGBX;
	RGBQUAD*				m_pDepthRGBX;

	int MapDepthToByte;
	int SkeletonCount;
	WCHAR UniqueID[256];

	void ConvertOpencvColorImage(cv::Mat *src, RGBQUAD* pBuffer, int nSizeBuffer);
	void ConvertOpencvGrayImage(cv::Mat *src, UINT16* pBuffer, int nHeight, int nWidth, int nDepthMinReliableDistance, int nDepthMaxDistance);
	void ProcessSkel(SkeletonInfo* m_SkeletonInfo, int nBodyCount, IBody** ppBodies, Mat *src, int mode);

	void DrawSkelToMat(Mat *src, Point2d *JointPoints, Joint* pJoints, int mode, int t_id);
	void DrawSkelBone(Mat *src, Joint* pJoints, Point2d* pJointPoints, JointType joint0, JointType joint1, Scalar t_Color);

	//Draw Hand state. - but not implemented.
	void DrawHand(Mat *src, HandState handState, Point2d& handposition);

	//Change CameraSpace coordinate to DepthCoordinate / ColorCoorinate.
	Point2d BodyToScreen(const CameraSpacePoint& bodyPoint, int mode);

	//intrinsic & extrinsic mat
	Mat Kmat;
	Mat Rmat;
	Mat Tmat;

	bool bDepth;
	bool bColor;
	bool bFace;
	bool bBody;
};

