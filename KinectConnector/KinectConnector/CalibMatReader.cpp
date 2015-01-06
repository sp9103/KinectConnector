#include "CalibMatReader.h"


CalibMatReader::CalibMatReader(void)
{
	m_Mat.create(4,4, CV_32FC1);
}


CalibMatReader::~CalibMatReader(void)
{
	m_Mat.release();
}


cv::Mat CalibMatReader::GetRTMat(char *filename, int ID){
	FILE *tfp = NULL;
	tfp = fopen(filename, "r");

	bool tFindflag;
	if(tfp != NULL)
		tFindflag = FindID(tfp, ID);

	if(tfp == NULL || !tFindflag){
		printf("File Not Found! return Identity matrix or Can not find Kinect ID\n");

		//Make 4*4 Identity matrix
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if(i == j)	m_Mat.at<float>(i,j) = 1.0f;
				else		m_Mat.at<float>(i,j) = 0.0f;
			}
		}

		return m_Mat;
	}

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			fscanf(tfp, "%f ", &m_Mat.at<float>(i,j));
			printf("%f ", m_Mat.at<float>(i,j));
		}
		printf("\n");
	}

	fclose(tfp);

	return m_Mat;
}

bool CalibMatReader::FindID(FILE *fp, int ID){
	bool tflag = false;
	char buf[16];

	sprintf(buf, "[%d]\n", ID);

	while(1){
		char temp;
		fscanf(fp, "%c", &temp);

		if(temp == buf[0]){
			tflag = findstr(fp, &buf[1]);

			if(tflag)
				return tflag;
		}

		if(feof(fp))
			break;
	}

	//tflag = findstr(fp, buf);

	fseek(fp, 0, SEEK_SET);

	return tflag;
}

bool CalibMatReader::findstr(FILE *fp, char *str){
	bool tflag = false;

	if(str[0] == '\n')
		return true;

	char temp;
	fscanf(fp, "%c", &temp);
	if(temp == str[0])
		tflag = findstr(fp, &str[1]);

	return tflag;
}