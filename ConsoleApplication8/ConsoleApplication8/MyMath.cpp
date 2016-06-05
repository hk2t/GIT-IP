#include "MyMath.h"

int MyMath::Rand(int min, int max) {
    return min + (rand() % (int)(max - min + 1));
}

int MyMath::ConvertToIndex(int cols, int row, int col) {
    return row*cols + col;
}

Vector<int> MyMath::ConvertToRowCol(int index, int cols) {
    Vector<int> v;
    int row = index/cols;
    int col = index-row*cols;
    v.push_back(row);
    v.push_back(col);
    return v;
}

void MyMath::Array1D(Mat mat) {
    for (int j=0; j<mat.rows; j++) {
		for (int i=0; i<mat.cols; i++) {
			mat.at<uchar>(Point(i, j)) = abs(mat.at<uchar>(Point(i, j)) - 255);
		}
	}
}