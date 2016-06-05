#include "cv.h"
//#include "highgui.h"
//#include "stdio.h"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <list>
//#include <conio.h> 
#include "MyPic.h"
#include "MyDataSet.h"
using namespace std;
using namespace cv;

MyPic::MyPic(String path, int flags){
   Init(path, flags, 7, 3);
}
MyPic::MyPic(String path, int flags, int datasetW, int datasetH){
    Init(path, flags, datasetW, datasetH);
}

// ��l��
void MyPic::Init(String path, int flags, int datasetW, int datasetH){
    mat = imread(path, flags);

    cout<<(int)(mat.at<uchar>(Point(0,0)))<<" / ";
    cout<<(int)(mat.at<uchar>(Point(1,0)))<<" / ";
    cout<<(int)(mat.at<uchar>(Point(2,0)))<<" / ";
    cout<<(int)(mat.at<uchar>(Point(3,0)))<<" / ";
    cout<<(int)(mat.at<uchar>(Point(4,0)))<<" / ";
    cout<<(int)(mat.at<uchar>(Point(5,0)))<<" / ";
    cout<<(int)(mat.at<uchar>(Point(6,0)))<<" / ";

    nMat.create(mat.rows, mat.cols, CV_32F);
    M_allLOF.create(mat.rows, mat.cols, CV_32F);
    this->datasetW = datasetW;
    this->datasetH = datasetH;

    this->rows = mat.rows;
    this->cols = mat.cols;

    for (int j=0; j<this->rows*this->cols; j++) {
        this->allLOF.push_back(0);
    }

    for (int j=0; j<nMat.rows; j++) {
        for (int i=0; i<nMat.cols; i++) {
            nMat.at<float>(Point(i, j)) = 0;
            M_allLOF.at<float>(Point(i, j)) = 0;
        }
    }
}

// �Ϥ��������
void MyPic::Show(String name){
    Show(name, mat);
}
void MyPic::Show(String name, Mat mat){
    imshow(name, mat);
}

// 7x1
void MyPic::Cal(){
    cout<<"mat(Rows,Cols)"<<rows<<" - "<<cols<<endl;

    for (int j=0; j<rows; j++) {
        MyDataSet myDataSet(datasetH, datasetW);
        myDataSet.Feed(GetDataSet(j, cols));
        myDataSet.ShowLOF();
        /*
        float total = 0;
        for (size_t x=0; x<myDataSet.data.size(); x++) {
            total += myDataSet.data[x].LOF;
            cout<<myDataSet.data[x].LOF<<", ";
        }
        cout<<endl;
        float mean = this->mean*(total/(float)myDataSet.data.size());
        for (size_t x=0; x<myDataSet.data.size(); x++) {
            if (myDataSet.data[x].LOF  >= mean) {
                Vector<int> rc = ConvertToRowCol((int)x, cols);
                int _row = (j)+rc[0];
                int _col = rc[1];

                //cout<<_row<<", "<<_col<<" - ";
               // if (_col == cols-1)
                nMat.at<float>(Point(_col, _row)) = myDataSet.data[x].LOF;

                //int _index = ConvertToIndex(_row, _col);
                //allLOF[_index] = myDataSet.data[x].LOF;
            }
        }
        cout<<endl;
        //break;
    }
    //ShowAllLOF(allLOF);
    cout<<endl;
    ShowAllLOF(nMat);
    */

    /*
    cout<<"ZZZ"<<endl;
    
    for (int j=0; j<nMat.rows; j++) {
        for (int i=0; i<nMat.cols; i++) {
            float lof = nMat.at<float>(Point(i,j));
            if (lof != 0) {
                int _row=j, _col=0;

                //int _index = ConvertToIndex(_row, _col);
                ////cout<<"r,c:"<<_row<<", "<<_col<<" - ";
                //allLOF[_index] = 1;

                Vector<Intensity> v0;
                //for (int _j=_row; _j<_row+this->datasetSize; _j++) {
                    for (int _i=_col; _i<_col+cols; _i++) {
                        Intensity I((int)mat.at<uchar>(Point(_i,_row)), _row, _i);
                        v0.push_back(I);
                    }
                //}
                Bubble_sort(v0);

                //for (size_t i=0; i<v0.size(); i++) {
                //    printf("(%d-%d,%d), ", v0[i].color, v0[i].row, v0[i].col);
                //}
                //printf("\n");

                Vector<int> vd;
                for (size_t _i=0; _i<v0.size()-1; _i++) {
                    vd.push_back(v0[_i+1].color-v0[_i].color);
                }

                //for (size_t i=0; i<vd.size(); i++) {
                //    printf("(%d), ", vd[i]);
                //}
                //printf("\n");

                int b0=0, b1=0;
                int i0, i1;
                for (size_t _i=0; _i<vd.size(); _i++) {
                    if ((int)_i < (this->datasetSize*this->datasetSize)/2) {
                        if (vd[_i] > b0) {
                            b0 = vd[_i];
                            i0 = _i;
                        }
                    }
                    else {
                        if (vd[_i] > b1) {
                            b1 = vd[_i];
                            i1 = _i;
                        }
                    }
                }
                b0 = v0[i0].color;
                b1 = v0[i1].color;
                //printf("b0=%d, b1=%d\n", b0, b1);

                int _index = ConvertToIndex(_row, _col);
                int curPoint = (int)mat.at<uchar>(Point(i,j));
                if (curPoint>b0 && curPoint<=b1) {
                    //allLOF[_index] = 0;

                }
                else {
                    //allLOF[_index] = 1;
                    M_allLOF.at<float>(Point(i, j)) = 1;
                }
                //break;
            }
        }
        //break;
    }

    //ShowAllLOF(allLOF);
    ShowAllLOF(M_allLOF);
    */
    cout<<"Cal-done";
    }
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

Vector<int> MyPic::GetDataSet(int row, int col){
    Vector<int> colors;
    for (int i=0; i<col; i++) {
        colors.push_back(mat.at<uchar>(Point(i,row)));
        cout<<(int)(mat.at<uchar>(Point(i,row)))<<" / ";
    }
    cout<<endl;
    return colors;
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