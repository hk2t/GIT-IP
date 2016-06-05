#include "cv.h"
#include "list"
#include "Intensity.h"
using namespace cv;

class MyPic
{
public:
    MyPic(String path, int flags, int datasetW);
public:
    Mat mat;
    Mat nMat;
    Vector<float> allLOF;
    Mat M_allLOF;// Àx¦s©Ò¦³LOF
    float mean;
public:
    void Show(String name);
    void Show(String name, Mat mat);
    void Cal();
    
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
    
    void ShowAllLOF(Mat mat);
    void ShowAllLOF(Vector<float> vec);
    void Bubble_sort(Vector<Intensity> v);
    //void CALCULATE();
};