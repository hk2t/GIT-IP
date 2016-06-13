#include "cv.h"
#include "MyData.h"
using namespace cv;

class MyDataSet
{
public:
    MyDataSet(int rows, int cols);
public:
    Vector<MyData> data;
    int rows;
    int cols;
public:
    void Feed(Vector<int> data);
    Vector<int> GetPointData(int row, int col);
    void ShowPointData(int row, int col);
    void ShowLRD();
    void ShowLOF();
private:
    void CalculateDist();
    void CalculateDist5(int index);
    void CalculateLRD();
    void CalculateLOF();
    void Bubble_sort(Vector<Cell> v);
    int ConvertToIndex(int row, int col);
};