#include "cv.h"
#include "highgui.h"
#include "stdio.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <list>
#include <conio.h> 
#include "MyPoint.h"
#include "MyPic.h"
#include "MyMath.h"
using namespace std;
using namespace cv;

void Create_week(int day, Mat img_small);
void Helper(MyPic pic, String lable);

int main(void) {
    char window_name[] = "Smoothing Demo";

    String imgName = "IMG_R0_GF.png";
    
    
    MyPic pic7x3("C:/Users/KIM/Desktop/GIT-PROJECT/MY-GIT/Image/"+imgName, CV_8UC1, 7);// 7
    //pic7x3.Cal(3.0);
    pic7x3.Cal(0);
    cout<<"LOF 7X3"<<endl;
    pic7x3.ShowAllLOF(pic7x3.nMat);
    Helper(pic7x3, "7x3");
    
    /*
    MyPic pic5x3("C:/Users/KIM/Desktop/GIT-PROJECT/MY-GIT/Image/"+imgName, CV_8UC1, 5);
    pic5x3.Cal(2);
    cout<<"LOF 5X3"<<endl;
    pic5x3.ShowAllLOF(pic5x3.nMat);
    Helper(pic5x3, "5x3");
    
    MyPic pic3x3("C:/Users/KIM/Desktop/GIT-PROJECT/MY-GIT/Image/"+imgName, CV_8UC1, 3);
    //pic3x3.Cal(1.5);
    //pic3x3.Cal(0);
    cout<<"LOF 3X3"<<endl;
    pic3x3.ShowAllLOF(pic3x3.nMat);
    Helper(pic3x3, "3x3");
    
    // Merge------------------
    Mat matMerge;
    matMerge.create(pic7x3.mat.rows, pic7x3.mat.cols, CV_32F);
    for (int j=0; j<matMerge.rows; j++) {
        for (int i=0; i<matMerge.cols; i++) {
            float result7x3 = pic7x3.nOMat.at<float>(Point(i, j));
            float result5x3 = pic5x3.nOMat.at<float>(Point(i, j));
            float result3x3 = pic3x3.nOMat.at<float>(Point(i, j));

            float mean7x3 = pic7x3.means.at<float>(Point(i, j));
            float mean5x3 = pic5x3.means.at<float>(Point(i, j));
            float mean3x3 = pic3x3.means.at<float>(Point(i, j));

            //float result = (result3x3*5 + result5x3*3 + result7x3*2)/(float)10;
            float result = (result3x3*3  + result7x3*1)/(float)4;
            //float mean = (mean7x3*5 + mean5x3*3 + mean3x3*2)/(float)10;
            float mean = (mean7x3*1 + mean3x3*3)/(float)4;
            //float result = (result3x3*5 + result5x3*2 + result7x3*1) /8;
            if (result >= 2.5) {//-----------------------------------------------------------<<
                matMerge.at<float>(Point(i, j)) = result;
            }
            else {
                matMerge.at<float>(Point(i, j)) = 0;
            }
        }
    }
    //imwrite("matMerge.png",matMerge);

    //ShowAllLOF(matMerge);

    MyPic picMerge("C:/Users/KIM/Desktop/GIT-PROJECT/MY-GIT/Image/"+imgName, CV_8UC1, matMerge);
    cout<<"LOF MERGE"<<endl;
    picMerge.ShowAllLOF(picMerge.nMat);
    Helper(picMerge, "MERGE");
    */
    waitKey(0);
    return 0;
}

void Create_week(int day, Mat img_small) {
    Mat result(img_small.rows, img_small.cols / 7, CV_8UC1);

    for (int i = 0, x = day; i<result.cols; i++) {
        for (int j = 0, y = 0; j<result.rows; j++) {
            if (x<img_small.cols && j<img_small.rows) {
                result.at<uchar>(Point(i, j)) = img_small.at<uchar>(Point(x, j));
            }
        }
        x = x + 7;
    }
    //cvtColor( "IMG_R"+to_string(day)+".png", gray_image, CV_BGR2GRAY );
    imwrite("IMG_R" + to_string(day) + ".png", result);
}

void Helper(MyPic pic, String lable){
    //Mat Source_Color;
    Mat dst1;

    Mat result1;
    result1.create(pic.mat.rows, pic.mat.cols, CV_8UC1);

    for (int j=0; j<pic.mat.rows; j++) {
        for (int i=0; i<pic.mat.cols; i++) {
            if ((double)pic.nMat.at<float>(Point(i, j)) != 0) {
                result1.at<uchar>(Point(i, j)) = 200;
            }
            else {
                result1.at<uchar>(Point(i, j)) = 0;
            }
        }
    }

    /*
    for (int j=0; j<result1.rows; j++) {
        printf("%2d-row: ", j);
        for (int i=0; i<result1.cols; i++) {
            int data = result1.at<uchar>(Point(i,j));
            if (data == 0) {
                printf("--- - ");
                continue;
            }
            else if (data < 10) {
                printf("00%d - ", data);
                 continue;
            }
            else if (data < 100) {
                printf("0%d - ", data);
                 continue;
            }
            printf("%d - ", data);
        }
        cout<<endl;
    }
    cout<<endl;
    */

    Mat big;
	Mat big1;
	/////////re_big and laplacian
	resize(result1, big,Size(), 10, 10, INTER_NEAREST);
	resize(pic.mat, big1, Size(), 10, 10, INTER_NEAREST);
	Laplacian( big, dst1, CV_8UC1, 1, 15, 0, BORDER_DEFAULT );
	imshow(lable+"laplacian", dst1);
	imwrite(lable+"lapla.png", dst1);
	imwrite(lable+"Gray_big.png", big);

			 
	 Mat dst_color(dst1.size(), CV_8UC3);
	 Mat big_color(big1.size(),CV_8UC3);
	 Mat result2(big1.size(), CV_8UC3);
	 cvtColor(dst1, dst_color, COLOR_GRAY2BGR);
	 cvtColor(big1, big_color, COLOR_GRAY2BGR);

	for (int j=0; j<big1.rows; j++) {
		for (int i=0; i<big1.cols; i++) {
			int B = dst_color.at<Vec3b>(Point(i, j))[0];
			int G = dst_color.at<Vec3b>(Point(i, j))[1];
			int R = dst_color.at<Vec3b>(Point(i, j))[2];
			if ( B==0 && G==0 && R==0) {
				result2.at<Vec3b>(Point(i, j))[0] = big_color.at<Vec3b>(Point(i, j))[0];
				result2.at<Vec3b>(Point(i, j))[1] = big_color.at<Vec3b>(Point(i, j))[1];
				result2.at<Vec3b>(Point(i, j))[2] = big_color.at<Vec3b>(Point(i, j))[2];

			}
			else {
				result2.at<Vec3b>(Point(i, j))[0] = 0;
				result2.at<Vec3b>(Point(i, j))[1] = 0;
				result2.at<Vec3b>(Point(i, j))[2] = 255;
			
			}
		}
	}
	imshow(lable+"result2", result2);
	imwrite(lable+"result2.png", result2);
}