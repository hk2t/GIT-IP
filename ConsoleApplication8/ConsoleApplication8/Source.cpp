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

Vector<int> Dist3(int colors[]);
int main(void) {
    //Mat Source_Color;
    Mat dst1;

    char window_name[] = "Smoothing Demo";

	MyPic pic33("C:/Users/KIM/Desktop/GIT-PROJECT/MY-GIT/Image/IMG_R0_GF.png", CV_8UC1, 7, 3);

    pic33.mean = 2;
    pic33.Cal();
    pic33.Show("pic33.png");


 //   /*MyMath::Array1D(pic33.mat);
 //   MyMath::Array1D(pic33_2.mat);*/

 //   pic33.mean = 3;
 //   pic33.Cal();

 //   for (int j=0; j<pic33.mat.rows; j++) {
	//	for (int i=0; i<pic33.mat.cols; i++) {
	//		pic33.mat.at<uchar>(Point(i, j)) = abs(pic33.mat.at<uchar>(Point(i, j)) - 255);
 //   	}
 //   }

 //   pic33.Show("pic33.png");
 //   
 //  /* pic33_2.mean = 2;
 //   pic33_2.Cal();
 //   pic33_2.Show("pic33_2.png");*/

 //   Mat result1;
 //   result1.create(pic33.mat.rows, pic33.mat.cols, CV_8UC1);

 //   for (int j=0; j<pic33.M_allLOF.rows; j++) {
 //       for (int i=0; i<pic33.M_allLOF.cols; i++) {
 //           if ((double)pic33.nMat.at<float>(Point(i, j)) != 0) {
 //               result1.at<uchar>(Point(i, j)) = 200;
 //           }
 //           else {
 //               result1.at<uchar>(Point(i, j)) = 0;
 //           }
 //       }
 //   }

 //   cout<<"Aaaaaaaa"<<endl;
 //   //pic33.ShowAllLOF(result1);
 //   for (int j=0; j<result1.rows; j++) {
 //       printf("%2d-row: ", j);
 //       for (int i=0; i<result1.cols; i++) {
 //           int data = result1.at<uchar>(Point(i,j));
 //           if (data == 0) {
 //               printf("--- - ");
 //               continue;
 //           }
 //           else if (data < 10) {
 //               printf("00%d - ", data);
 //                continue;
 //           }
 //           else if (data < 100) {
 //               printf("0%d - ", data);
 //                continue;
 //           }
 //           printf("%d - ", data);
 //       }
 //       cout<<endl;
 //   }
 //   cout<<endl;

 //   Mat big;
	//Mat big1;
	///////////re_big and laplacian
	//resize(result1, big,Size(), 10, 10, INTER_NEAREST);
	//resize(pic33.mat, big1, Size(), 10, 10, INTER_NEAREST);
	//Laplacian( big, dst1, CV_8UC1, 1, 15, 0, BORDER_DEFAULT );
	//imshow("laplacian", dst1);
	//imwrite("lapla.png", dst1);
	//imwrite("Gray_big.png", big);

	//		 
	// Mat dst_color(dst1.size(), CV_8UC3);
	// Mat big_color(big1.size(),CV_8UC3);
	// //Mat color = imread("L:/IMG_R4_fix.png", 1);
	// //Mat color = imread("L:/IMG_R0_fix_2.png", 1);
	// Mat result2(big1.size(), CV_8UC3);
	// //Mat big_color(big1.size(), CV_8UC3);
	// cvtColor(dst1, dst_color, COLOR_GRAY2BGR);
	// //resize(color, big_color, Size(), 10, 10, INTER_NEAREST);
	// cvtColor(big1, big_color, COLOR_GRAY2BGR);

	//for (int j=0; j<big1.rows; j++) {
	//	for (int i=0; i<big1.cols; i++) {
	//		int B = dst_color.at<Vec3b>(Point(i, j))[0];
	//		int G = dst_color.at<Vec3b>(Point(i, j))[1];
	//		int R = dst_color.at<Vec3b>(Point(i, j))[2];
	//		if ( B==0 && G==0 && R==0) {
	//			result2.at<Vec3b>(Point(i, j))[0] = big_color.at<Vec3b>(Point(i, j))[0];
	//			result2.at<Vec3b>(Point(i, j))[1] = big_color.at<Vec3b>(Point(i, j))[1];
	//			result2.at<Vec3b>(Point(i, j))[2] = big_color.at<Vec3b>(Point(i, j))[2];

	//		}
	//		else {
	//			result2.at<Vec3b>(Point(i, j))[0] = 0;
	//			result2.at<Vec3b>(Point(i, j))[1] = 0;
	//			result2.at<Vec3b>(Point(i, j))[2] = 255;
	//		
	//		}
	//	}
	//}
	//imshow("result2", result2);
	//imwrite("result2.png", result2);

    


    //pic77.mean = 6.5;
    //pic77.Cal();
    //pic77.Show("pic33.png");


    //picLena.Show("New_MyLena.PnG", picLena.nMat);

    /*
    int aa = 100;
    int *a = &aa;
    *a = 200;
    
    cout<<"a:"<<&a<<endl;
    cout<<*a;*/

    

    //v.push_back(1);
    //v.push_back(4);
    //v.push_back(3);
    //v.push_back(2);
    //
    //v[3] = 100;
    //for(size_t i=0; i<v.size(); i++) {
    //    cout << v[i]<< "\n";
    //}
    //cout<<"--"<<v[2];
    //
    //while (true)
    //    {

    //    }

    //list<int>::iterator it;
    //list<int> myList;
    //myList.push_back(5);
    //myList.push_back(6);
    //myList.push_back(1);
    //myList.push_back(0);

    //
    //for (it=myList.begin(); it!=myList.end(); it++) {
    //    cout<<"a"<<*it<<"\n";
    //}
    //myList.sort();
    //for (it=myList.begin(); it!=myList.end(); it++) {
    //    cout<<"b"<<*it<<"\n";
    //}
    //getchar( );

    /*
    Source_Color = imread("L:/OneHour_2.png", CV_8UC1);//color image
    cout << Source_Color.rows << " - " << Source_Color.cols;

    Mat lena = imread("L:/lenanoise.PNG", 0);//3 onehour
    imshow("daylly.png", lena);
    //Mat daylly(daylly1.size(),CV_8UC1);

    //for (int j=0; j<daylly1.rows; j++) {
    //for (int i=0; i<daylly1.cols; i++) {
    //daylly.at<uchar>(Point(i, j)) = abs(daylly1.at<uchar>(Point(i, j)) - 255);
    //}
    //}
    //imwrite("newGray.png",daylly);

    Mat Image_small(Source_Color.rows / 20, Source_Color.cols / 10, CV_8UC1);
    ///small
    for (int i = 0, x = 0; x<Source_Color.cols; i++, x = x + 10) {
        for (int j = 0, y = 0; y<Source_Color.rows; j++, y = y + 20) {
            if (i<Image_small.cols && j<Image_small.rows) {
                Image_small.at<uchar>(Point(i, j)) = Source_Color.at<uchar>(Point(x, y));
            }
        }
    }

    for (int i = 0; i<7; i++) {
        Create_week(i, Image_small);
    }
    imwrite("IMG_SM.png", Image_small);
    ///Apply median filter



    for (int i = 0; i<lena.rows; i++) {
        for (int j = 0; j<lena.cols; j++) {

        }
    }

    int a[10];
    cout << "\na = " << (sizeof(a) / sizeof(*a));
    Bubble_sort(a);
    //*/
    

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


Vector<int> Dist3(int colors[]){
    Vector<int> _v;
    for (size_t i=0; i<10; i++) {
        //_v[i] = (size_t)Rand(0, 100);
        _v.push_back(1);
    }
    //++ sort
    return _v;
}