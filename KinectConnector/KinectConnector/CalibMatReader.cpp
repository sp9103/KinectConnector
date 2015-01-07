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

	printf("[%d] Kinect Trasformation matrix : \n", ID);
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

bool compare(matarr &a, matarr &b){
	return a.ID < b.ID;
}

void CalibMatReader::writeRTMat(char *filename, cv::Mat mat, int ID){
	//read & copy
	FILE *tfp = NULL;
	int datacount = 0;
	matarr temparr;

	std::vector<matarr> matVec; 

	tfp = fopen(filename, "r");

	if(tfp != NULL){
		fscanf(tfp, "%d\n", &datacount);

		for(int i = 0; i < datacount; i++){
			fscanf(tfp, "[%d]\n", &temparr.ID);
			for(int j = 0; j < 16; j++){
				fscanf(tfp, "%f ", &temparr.element[j]);
			}
			fscanf(tfp, "\n");
			matVec.push_back(temparr);
		}

		fclose(tfp);
	}

	//rewrite - 넣고 순서대로 정렬 (덮어쓰기)
	int idx = -1;

	//기존 데이터 있으면 지우고 새로씀
	for(int i = 0; i < matVec.size(); i++){
		if(ID == matVec.at(i).ID){
			matVec.erase(matVec.begin() + i);
			datacount--;
			break;
		}
	}

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			temparr.element[i*4 + j] = mat.at<float>(i,j);
		}
	}
	temparr.ID = ID;
	matVec.push_back(temparr);
	std::sort(matVec.begin(), matVec.end(), compare);

	tfp = fopen(filename, "w");
	fprintf(tfp, "%d\n", ++datacount);
	for(int i = 0; i < matVec.size(); i++){
		fprintf(tfp, "[%d]\n", matVec.at(i).ID);
		for(int j = 0; j < 16; j++){
			fprintf(tfp, "%f ", matVec.at(i).element[j]);
		}
		fprintf(tfp, "\n");
	}

	fclose(tfp);
}