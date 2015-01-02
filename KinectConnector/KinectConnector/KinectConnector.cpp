#include "KinectConnector.h"


KinectConnector::KinectConnector(void)
{
	bDepth = bColor = bFace = bBody = false;

	m_pColorRGBX = new RGBQUAD[KINECT_COLOR_HEIGHT * KINECT_COLOR_WIDTH];
	m_pDepthRGBX = new RGBQUAD[KINECT_DEPTH_HEIGHT * KINECT_DEPTH_WIDTH];

	MapDepthToByte = 8000 / 256;
}


KinectConnector::~KinectConnector(void)
{
	if(m_pColorRGBX){
		delete [] m_pColorRGBX;
		m_pColorRGBX = NULL;
	}
	if(m_pDepthRGBX){
		delete [] m_pDepthRGBX;
		m_pDepthRGBX = NULL;
	}

	SafeRelease(m_pBodyFrameReader);
	SafeRelease(m_pCoordinateMapper);

	Kmat.release();
	Rmat.release();
	Tmat.release();
}
