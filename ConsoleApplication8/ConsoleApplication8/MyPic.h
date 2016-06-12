#include "cv.h"
#include "list"
#include "Intensity.h"
using namespace cv;

class MyPic
{
public:
    MyPic(String path, int flags, int datasetW);
    MyPic(String path, int flags, Mat nMat);
public:
    Mat mat;
    Mat nMat;// saved all LOF
    Mat nOMat;// saved all LOF
    Mat means;
public:
    void Show(String name);
    void Show(String name, Mat mat);
    void Cal(float mean);
    void ShowAllLOF(Mat mat);
private:
    int datasetW, datasetH;
    int rows;
    int cols;
private:
    void Init(String path, int flags, int datasetW, int datasetH);
    Vector<int> GetDataSet(int row, int col);
    int Rand(int min, int max);
    int ConvertToIndex(int row, int col);
    Vector<int> ConvertToRowCol(int index, int cols);
    void ShowAllLOF(Vector<float> vec);
    void Bubble_sort(Vector<Intensity> v);
    //void CALCULATE();
};