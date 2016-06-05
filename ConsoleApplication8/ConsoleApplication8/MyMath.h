#include "cv.h"
using namespace cv;

class MyMath
{
    public:
        static int Rand(int, int);
        static int ConvertToIndex(int, int, int);
        static Vector<int> ConvertToRowCol(int, int);
        static void Array1D(Mat);
};