#include "define.h"

class CalibMatReader
{
public:
	CalibMatReader(void);
	~CalibMatReader(void);

	cv::Mat GetRTMat(char *filename, int ID);
	void writeRTMat(char *filename, cv::Mat mat, int ID);

private:
	cv::Mat m_Mat;

	bool FindID(FILE *fp, int ID);
};

