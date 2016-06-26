#include "cv.h"
#include "Cell.h"
using namespace cv;

class MyData
{
public:
    MyData();
    MyData(int data);

    Vector<Cell> dist3;
    int color;// 0~255
    Vector<Cell> dist;
    float LFD;

    float LOF;
};