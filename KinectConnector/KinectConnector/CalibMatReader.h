#include "define.h"

typedef struct _matarr
{
	int ID;
	float element[16];
}matarr;

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
	bool findstr(FILE *fp, char* str);
};

