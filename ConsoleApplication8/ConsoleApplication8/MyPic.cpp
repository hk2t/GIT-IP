#include "cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "MyPic.h"
#include "MyDataSet.h"
using namespace std;
using namespace cv;

MyPic::MyPic(String path, int flags, int datasetW){
    Init(path, flags, datasetW, 3);
}
MyPic::MyPic(String path, int flags, Mat nMat){
    mat = imread(path, flags);
    this->rows = mat.rows;
    this->cols = mat.cols;
    this->nMat = nMat;
}

// 初始化
void MyPic::Init(String path, int flags, int datasetW, int datasetH){
    // 創建 MAT
    mat = imread(path, flags);

    // 黑->白
    for (int j=0; j<mat.rows; j++) {
		for (int i=0; i<mat.cols; i++) {
			mat.at<uchar>(Point(i, j)) = abs(mat.at<uchar>(Point(i, j)) - 255);
		}
	}

    nMat.create(mat.rows, mat.cols, CV_32F);
    nOMat.create(mat.rows, mat.cols, CV_32F);
    means.create(mat.rows, mat.cols, CV_32F);
    this->datasetW = datasetW;
    this->datasetH = datasetH;

    this->rows = mat.rows;
    this->cols = mat.cols;

    for (int j=0; j<nMat.rows; j++) {
        for (int i=0; i<nMat.cols; i++) {
            nMat.at<float>(Point(i, j)) = 0;
            nOMat.at<float>(Point(i, j)) = 0;
            means.at<float>(Point(i, j)) = 0;
        }
    }
}

// 圖片視窗顯示
void MyPic::Show(String name){
    Show(name, mat);
}
void MyPic::Show(String name, Mat mat){
    imshow(name, mat);
}

// 7x1
void MyPic::Cal(float mean){
    cout<<"matt(Rows,Cols)"<<rows<<" - "<<cols<<endl;
    int d = datasetH/2;
    for (int j=d; j<rows-d; j++) {
        for (int i=datasetW-1; i<cols; i++) {
            MyDataSet myDataSet(datasetW, datasetW);
            myDataSet.Feed(GetDataSet(j, i));
            //myDataSet.ShowLOF();// hien thi LOF
            //cout<<endl;
            float total = 0;
            for (size_t x=0; x<myDataSet.data.size(); x++) {
                total += myDataSet.data[x].LOF;
            }

            float _mean = mean*(total/(float)myDataSet.data.size());
            //float _mean = mean;
            for (size_t x=0; x<myDataSet.data.size(); x++) {
                Vector<int> rc = ConvertToRowCol((int)x, datasetW);
                int _row = (j-d)+rc[0];
                int _col = (i-(datasetW-1))+rc[1];
                if (myDataSet.data[x].LOF  >= _mean) {
                    //if (nMat.at<float>(Point(_col, _row)) == 0) {
                    //    if (_col < datasetW-1 || _row < d || _row >= rows-d) {
                    //        nMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                    //    }
                    //    if (_col == i && _row == j) {
                    //        nMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                    //    }
                    //    /*else {
                    //        nMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                    //    }*/
                    //}
                    
                    if (_col < datasetW-1 || _row < d || _row >= rows-d) {
                        nMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                    }
                    //else {
                    //    nMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                    //}
                    if (_col == i && _row == j && nMat.at<float>(Point(_col, _row)) == 0) {
                        nMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                    }
                }

                // means
                // means.at<float>(Point(_col, _row)) = _mean;

                // nOMat
                /*if (_col < datasetW-1 || _row < d || _row >= rows-d) {
                    nOMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                }*/
                //else {
                //    nOMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                //}
                /*if (_col == i && _row == j && nOMat.at<float>(Point(_col, _row)) == 0) {
                    nOMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;
                }*/
            }
        }
    }
    //cout<<endl;
    //ShowAllLOF(nMat);
}

Vector<int> MyPic::GetDataSet(int row, int col){
    int d = datasetH/2;
    Vector<int> colors;
    for (int j=row-d; j<=row+d; j++) {
        for (int i=col-(datasetW-1); i<=col; i++) {
            int color = mat.at<uchar>(Point(i, j));
            colors.push_back(color);
        }
    }
    colors.pop_back();
    // DEBUG
    /*
    cout<<"COLORS: ";
    for (size_t x=0; x<colors.size(); x++) {
        cout<<colors[x]<<", ";
    }
    cout<<endl;*/
    return colors;
}

void MyPic::ShowAllLOF(Mat mat) {
    for (int j=0; j<this->rows; j++) {
        printf("%2d-row: ", j);
        for (int i=0; i<this->cols; i++) {
            float data = mat.at<float>(Point(i,j));
            if (data == 0) {
                printf("-------- - ");
                continue;
            }
            else if (data < 10) {
                printf("0%2.5f - ", data);
                 continue;
            }
            printf("%2.5f - ", data);
        }
        cout<<endl;
    }
    cout<<endl;
}

void MyPic::ShowAllLOF(Vector<float> vec) {
    for (int j=0; j<this->rows; j++) {
        printf("%2d-row: ", j);
        for (int i=0; i<this->cols; i++) {
            float data = vec[ConvertToIndex(j, i)];
            if (data == 0) {
                printf("-------- - ");
                continue;
            }
            else if (data < 10) {
                printf("0%2.5f - ", data);
                 continue;
            }
            printf("%2.5f - ", data);
        }
        cout<<endl;
    }
    cout<<endl;
}

int MyPic::Rand(int min, int max){
    return min + (rand() % (int)(max - min + 1));
}

int MyPic::ConvertToIndex(int row, int col){
    return row*this->cols + col;
}

Vector<int> MyPic::ConvertToRowCol(int index, int cols){
    Vector<int> v;
    int row = index/cols;
    int col = index-row*cols;
    v.push_back(row);
    v.push_back(col);
    return v;
}

void MyPic::Bubble_sort(Vector<Intensity> v) {
    for (size_t i = 0; i<v.size() - 1; i++) {
        for (size_t j = 0; j<v.size() - 1 - i; j++) {
            if (v[j].color > v[j + 1].color) {
                int temp = v[j].color;
                v[j].color = v[j + 1].color;
                v[j + 1].color = temp;
            }
        }
    }
}